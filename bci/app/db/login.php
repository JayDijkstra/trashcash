<?php
/**
 * Created by PhpStorm.
 * User: Jay
 * Date: 8-7-2015
 * Time: 18:22
 */
session_start();
require_once 'connect.php';


    $username = mysqli_real_escape_string($con,$_POST['username']);
    $password = mysqli_real_escape_string($con, $_POST['password']);

    $query = mysqli_query($con, "select * from users where password='$password' AND username='$username'");

    $rows = mysqli_num_rows($query);

    if($rows == 1){
        $_SESSION['username']= $username;
        header("location: ../home.php");
    }




