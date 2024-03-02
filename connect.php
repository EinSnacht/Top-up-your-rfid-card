<?php
$servername = "127.0.0.1";
$username = "root";
$password = "******";   //use your password to log in phpmyadmin or when you setuo install appserv
$database = "******";   //your database name

// Create connection
$con = new mysqli($servername, $username, $password, $database);

// Check connection
if ($con->connect_error) {
    die("Connection failed: " . $con->connect_error);
}

// Set utf8 charset
mysqli_set_charset($con, "utf8");
?>
