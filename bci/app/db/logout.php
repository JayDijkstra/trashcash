<?php
/**
 * Created by PhpStorm.
 * User: Jay
 * Date: 9-7-2015
 * Time: 00:19
 */
session_start();
if(session_destroy()) // Destroying All Sessions
{
    header("Location: ../index.html"); // Redirecting To Home Page
}