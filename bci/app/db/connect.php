<?php
/**
 * Created by PhpStorm.
 * User: Jay
 * Date: 8-7-2015
 * Time: 17:02
 */
$con = mysqli_connect("localhost", "demo", "demo");
mysqli_select_db($con,'trashcash');

if(mysqli_connect_errno()){
    echo "Database is gefaald";
}

