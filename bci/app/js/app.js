/**
 * Created by Jay on 7/6/2015.
 */
var app = angular.module('TrashCash', []);

app.run(function ($rootScope) {
    $rootScope.name = "Object 1";
});

app.controller('RewardController', function ($scope) {
    $scope.rewards = [
        {
            name: "Korting op Diergaarde Blijdorp",
            description: "Gezellig met de familie naar de dierentuin",
            points: 1000,
            img: "image/blijdorp.gif"
        },
        {
            name: "25% korting op Bol.com boeken",
            description: "Voor de echte boekenworm 25% korting op " +
            "het gehele boek assortiment!",
            points: 1000,
            img: "image/bol.jpg"
        },
        {
            name: "1 Maand gratis Xbox Live",
            description: "Gamen doe je het liefst met je vrienden! Ga daarom voor Xbox-live!",
            points: 2000,
            img: "image/xbox.png"
        },
        {
            name: "Vrijkaarten Gamescom 2015 (Duitsland)",
            description: "Ga erop uit om de nieuwste en tofste games te ontdekken! Live op GamesCom!",
            points: 3000,
            img: "image/gamescom.jpg"
        },
        {
            name: "Gratis Happy Meal bij McDonalds",
            description: "Een lekker zakje friet, een verse hamburger en een cool speeltje",
            points: 300,
            img: "image/mc.png"
        }
    ]
});

app.controller('AchievementsController', function ($scope) {
    $scope.achievements =
        [
            {
                name: "Starter",
                description: "Maak voor het eerst gebruik van TrashCash",
                points: 5,
                earned: "nee",
                img: "image/starter.png"
            },
            {
                name: "Collector",
                description: "Gooi 10 producten weg",
                points: 100,
                earned: "nee",
                img: "image/collector.png"
            },
            {
                name: "Not in my yard",
                description: "Gooi 20 producten weg",
                points: 200,
                earned: "ja",
                img: "image/nimy.png"
            },
            {
                name: "It is Garbageday!",
                description: "Gebruik gemaakt van meerdere TrashCash producten",
                points: 300,
                earned: "nee",
                img: "image/gd.png"
            },
            {
                name: "Garbage Hoarder",
                description: "Gooi 10 (niet-van-hier-merken) in een TrashCash prullenbak",
                points: 100,
                earned: "nee",
                img: "image/hoarder.png"
            }
        ]
});





