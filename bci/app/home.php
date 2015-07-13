<?php
session_start();
if (!isset($_SESSION['username'])) {
  header('Location: index.html');
  exit;
}
?>
<!DOCTYPE html>
<html ng-app="TrashCash">
<head lang="en">
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>TrashCash portal</title>
    <link rel="stylesheet" href="css/bootstrap.min.css"/>
    <link rel="stylesheet" href="css/style.css"/>
</head>
<body ng-controller="RewardController">
<nav class="navbar navbar-default">
    <div class="container-fluid">
        <div class="navbar-header">
            <a class="navbar-brand" href="#">TrashCa$h</a>
        </div>
        <div>
            <ul class="nav navbar-nav">
                <li class="active"><a href="home.php">Home</a></li>
                <li><a href="achievements.php">Mijn Achievements</a></li>
            </ul>
            <ul class="nav navbar-nav navbar-right">
                <li><a href="#" id="points-overview">Punten</a></li>
                <li><a href="db/logout.php">Uitloggen</a></li>
            </ul>

        </div>
    </div>
</nav>

<div id="reward-wrapper">
    <div class="row row-list" ng-repeat="reward in rewards">

        <div class="col-md-6">
        <img class="pull-left" ng-src="{{reward.img}}"/>
            <h3>{{reward.name}}</h3>
            <p>{{reward.description}}</p>
            <p><button class="btn-info pull-right">{{reward.points}} Punten</em></button></p>
        </div>
        <div class="clearfix visible-lg"></div>
    </div>
</div>
</div>

<div id="name-data"></div>

<!-- Hosted Libraries -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
<script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.0.7/angular.min.js"></script>

<!-- Includes -->
<script src="js/bootstrap.min.js"></script>
<script src="js/app.js"></script>
<script src="js/main.js"></script>

</body>
</html>