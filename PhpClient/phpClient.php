/**
* Created by PhpStorm.
* User: haohanwang
* Date: 9/25/15
* Time: 10:49 AM
*/

<html>

<head>
    <title>PHP SOCEKT</title>
</head>

<body>
<?php

function startsWith($haystack, $needle, $case = true)
{
    if ($case)
        return strpos($haystack, $needle, 0) === 0;

    return stripos($haystack, $needle, 0) === 0;
}

function endsWith($haystack, $needle, $case = true)
{
    $expectedPosition = strlen($haystack) - strlen($needle);

    if ($case)
        return strrpos($haystack, $needle, 0) === $expectedPosition;

    return strripos($haystack, $needle, 0) === $expectedPosition;
}

function json_encoder_format($var)
{
    if (gettype($var) == "array") {
        $class = '"vector"';
        $type = gettype($var[0]);
        if ($type == "double"){
            $type = "float";
        }
        $type = '"'.$type .'"';
        $size = count($var);
        $str = '{"class":' . $class . ',"type":' . $type . ',"size":' . $size . ',"value":{';
        for ($a = 0; $a < $size - 1; $a++) {
            $str = $str . '"' . $a . '":' . $var[$a] . ',';
        }
        $ind = $size - 1;
        $str = $str . '"' . $ind . '":' . $var[$size - 1] . '}}';

        return $str;
    } else {
        $class = "single_value";
        $type = gettype($var);
        $size = 1;
        $str = '{"class":' . $class . ',"type":' . $type . ',"size":' . $size . ',"value":' . $var . '}';
        return $str;
    }
}

function json_decoder_single_value($message){
    $var = json_decode($message);
    $value = $var->{"value"};
    return $value;
}

function json_decoder_vector($message){
    $var = json_decode($message);
    $size = $var->{"size"};
    $value = [];
    for ($a=0;$a<$size;$a++){
        $value[] = $var->{"value"}->{$a};
    }
    return $value;
}


function connect()
{
    global $sock;
    if (!($sock = socket_create(AF_INET, SOCK_STREAM, 0))) {
        $errorcode = socket_last_error();
        $errormsg = socket_strerror($errorcode);

        die("Couldn't create socket: [$errorcode] $errormsg \n");
    }

    echo "Socket created";

    if (!socket_connect($sock, 'localhost', 55777)) {
        $errorcode = socket_last_error();
        $errormsg = socket_strerror($errorcode);

        die("Could not connect: [$errorcode] $errormsg \n");
    }

    echo "Connection established <br>";
}

function send_message($message)
{
    global $sock;
    if (!socket_send($sock, $message, strlen($message), 0)) {
        $errorcode = socket_last_error();
        $errormsg = socket_strerror($errorcode);

        die("Could not send data: [$errorcode] $errormsg \n");
    }

    echo "Message send successfully<br>";
}

function get_message()
{
    global $sock;
    if (socket_recv($sock, $buf, 65535, MSG_WAITALL) === FALSE) {
        $errorcode = socket_last_error();
        $errormsg = socket_strerror($errorcode);

        die("Could not receive data: [$errorcode] $errormsg \n");
    }
    $pos = strpos($buf, "\0");
    return substr($buf, 0, $pos);
}

//$message = "{\"size\":3,\"type\":\"float\",\"class\":\"vector\",\"value\":{\"0\":0.89291495,\"1\":0.6799756,\"2\":0.10601133}}";
//
$variable = array(0.123, 0.234, 0.566, 0.001, 0.345);
$message = json_encoder_format($variable);

connect();
send_message($message);
$message = get_message();
$var = json_decoder_vector($message);
echo var_dump($var);

?>
</body>

</html>
