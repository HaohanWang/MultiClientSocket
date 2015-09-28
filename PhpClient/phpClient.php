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

$message = "{\"size\":3,\"type\":\"float\",\"class\":\"vector\",\"value\":{\"0\":0.89291495,\"1\":0.6799756,\"2\":0.10601133}}";

//Send the message to the server
if (!socket_send($sock, $message, strlen($message), 0)) {
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);

    die("Could not send data: [$errorcode] $errormsg \n");
}

echo "Message send successfully<br>";

if (socket_recv($sock, $buf, 65535, MSG_WAITALL) === FALSE) {
    $errorcode = socket_last_error();
    $errormsg = socket_strerror($errorcode);

    die("Could not receive data: [$errorcode] $errormsg \n");
}

//print the received message
echo $buf;

?>
</body>

</html>
