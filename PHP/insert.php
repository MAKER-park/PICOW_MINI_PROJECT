<?php
$servername = "127.0.0.1";
$username = "park";
$password = "134625Wo@";
$dbname = "esp_db";
 
$conn = mysqli_connect($servername, $username, $password, $dbname);
 
$temp = $_GET['temp'];
$hum = $_GET['hum'];
$pm1 = $_GET['pm1'];
$pm2 = $_GET['pm2'];
$pm3 = $_GET['pm3'];

$sql = "INSERT INTO `project`( `temp`, `hum`, `pm1.0`, `pm2.5`, `pm10`) VALUES ($temp, $hum, $pm1, $pm2, $pm3)";
 
mysqli_query($conn, $sql);
mysqli_close($conn);
?>
