--Query 1
SELECT *
FROM player
WHERE player.position = 2;
--Query 2
SELECT player.name, player.age
FROM player
WHERE (player.position = 1) AND (player.team = "Rays");
--Query 3
SELECT player.name, player.number, player.team
FROM player
WHERE (player.position BETWEEN 7 and 9) AND (player.age <= 25);
--QUERY 4
SELECT player.name, player.number
FROM player
WHERE (player.position BETWEEN 3 and 6) AND (player.team = "Red Sox");
--QUERY 5
SELECT player.name, player.number, player.team
FROM player
WHERE (player.position = 1) AND (player.age > 30);
