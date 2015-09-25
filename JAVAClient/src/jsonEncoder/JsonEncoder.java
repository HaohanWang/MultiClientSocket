package jsonEncoder;

import java.io.IOException;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;

public class JsonEncoder<T> {
	private static JsonEncoder instance = null;

	public static <T> JsonEncoder getInstance() {
		if (instance == null) {
			instance = new JsonEncoder<T>();
		}
		return instance;
	}

	static public String getType(Object obj) {
		String[] strs = obj.getClass().getName().split(Pattern.quote("."));
		int len = strs.length;
		return strs[len - 1].toLowerCase();
	}

	private JsonEncoder() {
	};

	static private String object2string(JSONObject obj) {
		StringWriter out = new StringWriter();
		try {
			obj.writeJSONString(out);
		} catch (IOException e) {
			e.printStackTrace();
		}
		String jsonText = out.toString();
		return jsonText;
	}

	static public <T> String encode(List<T> input) {
		JSONObject obj = new JSONObject();
		obj.put("class", "vector");
		obj.put("type", getType(input.get(0)));
		obj.put("size", input.size());
		JSONObject value = new JSONObject();
		for (int i = 0; i < input.size(); i++) {
			value.put(Integer.toString(i), input.get(i));
		}
		obj.put("value", value);
		return object2string(obj);
	}

	static public <T> String encode(T input) {
		JSONObject obj = new JSONObject();
		obj.put("class", "single_value");
		obj.put("type", getType(input));
		obj.put("size", 1);
		obj.put("value", input);
		return object2string(obj);
	}

	static public <T> ArrayList<T> decode_vector(String s) {

		int len = s.indexOf("\0");
		String str = s.substring(0, len);

		Map map = (JSONObject) JSONValue.parse(str);

		if (map == null) {
			System.out.println("Why I am null");
		}

		if (map.isEmpty()) {
			System.out.println("How come I am empty");
		}

		if (!map.get("class").equals("vector")) {
			System.err.println("This method is only used for List");
			return null;
		}
		String type_ = (String) map.get("type");
		int size_ = Integer.parseInt((String) map.get("size"));
		String value_ = (String) map.get("value").toString();

		if (type_.equals("int")) {
			ArrayList<Integer> result = new ArrayList<Integer>();
			Map v_map = (JSONObject) JSONValue.parse(value_);
			for (int i = 0; i < size_; i++) {
				result.add((Integer) v_map.get(Integer.toString(i)));
			}
			return (ArrayList<T>) result;
		} else if (type_.equals("float")) {
			ArrayList<Float> result = new ArrayList<Float>();
			Map v_map = (JSONObject) JSONValue.parse(value_);
			for (int i = 0; i < size_; i++) {
				result.add((float) Float.parseFloat((String) v_map.get(Integer
						.toString(i))));
			}
			return (ArrayList<T>) result;
		} else if (type_.equals("string")) {
			ArrayList<String> result = new ArrayList<String>();
			Map v_map = (JSONObject) JSONValue.parse(value_);
			for (int i = 0; i < size_; i++) {
				result.add((String) v_map.get(Integer.toString(i)));
			}
			return (ArrayList<T>) result;
		} else {
			System.err.println("Have not implemented decode method for Tpye"
					+ type_);
		}
		return null;
	}

	static public <T> Object decode_single_value(String str) {
		Map map = (JSONObject) JSONValue.parse(str);
		if (!map.get("class").equals("single_value")) {
			System.err
					.println("This method is only used for Single Value Variable");
			return null;
		}
		String type_ = (String) map.get("type");
		int size_ = Integer.parseInt((String) map.get("size"));
		String value_ = (String) map.get("value");
		if (type_.equals("int")) {
			int r = Integer.parseInt(value_);
			return r;
		} else if (type_.equals("folat")) {
			float r = Float.parseFloat(value_);
			return r;
		} else if (type_.equals("string")) {
			return value_;
		} else {
			System.err.println("Have not implemented decode method for Tpye"
					+ type_);
		}
		return null;
	}
}
