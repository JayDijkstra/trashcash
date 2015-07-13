<?php
 
require '../db/connect.php';

$points = $_GET['points'];

$query = mysqli_query($con, "UPDATE users
SET points = points + '$points'
WHERE username= 'Jay'");

?>