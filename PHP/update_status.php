<?php
$servername = "127.0.0.1";
$username = "park";
$password = "134625Wo@";
$dbname = "esp_db";

$conn = mysqli_connect($servername, $username, $password, $dbname);

$status = $_GET['status'];
$R = $_GET['R'];
$G = $_GET['G'];
$B = $_GET['B'];

$sql = "UPDATE `project_status` SET `status`=$status,`R`=$R,`G`=$G,`B`=$B WHERE 1";

mysqli_query($conn, $sql);
mysqli_close($conn);
?>


