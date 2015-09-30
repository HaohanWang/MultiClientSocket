# MultiClientSocket 

#### A socket example for CPP clients, JAVA clients, PHP clients to connect to CPP server simultaneously. 

	CPP Server: Hold clients simutaneously with threads
	CPP Client: Send/Receive Message from Server
	JAVA Client: Send/Receive Message from Server 
	PHP Client: Send/Receive Message from Server

#### A JSON PROTOCOL for sending/receiving information
	
	class: the dimension of data transferred: single_value, vector, matrix
	type: the type of data transferred: int, float, string
	size: size of data transferred (invalid if class is set to single_value)
	value: the actual value

#### An example of how JAVA/CPP/PHP can call or be called directly within the same server
