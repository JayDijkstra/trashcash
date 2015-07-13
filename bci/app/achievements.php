<?php
session_start();
if (!isset($_SESSION['username'])) {
    header('Location: index.html');
    exit;
}
?>

<!DOCTYPE html>
<html ng-app="TrashCash">
<head>
    <title>Achievements</title>
    <link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="css/style.css">
</head>
<body ng-controller="AchievementsController">

<nav class="navbar navbar-default">
    <div class="container-fluid">
        <div class="navbar-header">
            <a class="navbar-brand" href="#">TrashCa$h</a>
        </div>
        <div>
            <ul class="nav navbar-nav">
                <li><a href="home.php">Home</a></li>
                <li class="active"><a href="achievements.php">Mijn Achievements</a></li>
                <li><a href="#"></a></li>
            </ul>
            <ul class="nav navbar-nav navbar-right">
                <li><a href="#" id="points-overview">Punten</a></li>
                <li><a href="db/logout.php">Uitloggen</a></li>
            </ul>
        </div>
    </div>
</nav>
<table class="table table-striped table-bordered" cellspacing="0" width="100%">
    <thead>
    <tr>
        <th>#</th>
        <th>Achievement</th>
        <th>Beschrijving</th>
        <th>Punten</th>
        <th>Behaald</th>
    </tr>
    </thead>
    <tbody>
    <tr ng-repeat="achievement in achievements">
        <td><img ng-src="{{achievement.img}}" class="center-block"></td>
        <td>
            {{achievement.name}}
        </td>

        <td>{{achievement.description}}</td>
        <td>{{achievement.points}}</td>
        <td>{{achievement.earned}}</td>
    </tr>
    </tbody>
</table>
<!-- Hosted Libraries -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
<script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.0.7/angular.min.js"></script>

<!-- Includes -->
<script src="js/bootstrap.min.js"></script>
<script src="js/app.js"></script>
<script src="js/main.js"></script>
</body>
</html>