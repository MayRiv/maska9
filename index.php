<?php
	require("viewer.inc");
	require("DBManager.inc");
	require("System.inc");
	$host = "localhost";
	$dbName = "maska9";
	$user = "root";
	$password = "";
	DBManager::getInstance()->connect($host, $dbName, $user, $password);

	if (isset($_GET['action']))
	{
		if ($_GET['action'] == 'getTeams')
			System::getInstance()->getTeams();
		else if ($_GET['action'] == 'getGames')
			System::getInstance()->getGames();
		else if ($_GET['action'] == 'insertGame')
			System::getInstance()->insertGame();
		else 
			System::getInstance()->getPlayers();
	}
	else 
		System::getInstance()->getPlayers();
?>
