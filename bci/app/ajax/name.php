<?php
/**
 * Created by PhpStorm.
 * User: Jay
 * Date: 8-7-2015
 * Time: 17:04
 */
    require '../db/connect.php';
    session_start();
    $username = $_SESSION['username'];

    $query = "select points from users where username='$username'";

    $result = $con->query($query);

    if($result->num_rows > 0){
        while($row = $result->fetch_assoc()){
            echo $row['points'];
        }
    }




