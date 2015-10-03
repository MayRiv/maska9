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
		else if ($_GET['action'] == 'adminPanel')
			System::getInstance()->getAdminPanel();
		else if ($_GET['action'] == 'insertGame')
			System::getInstance()->insertGame();
		else if ($_GET['action'] == 'showGames')
			System::getInstance()->showGames();
		else if ($_GET['action'] == 'getPlacing')
			System::getInstance()->getPlacing();
		else 
			System::getInstance()->getTeams();
	}
	else 
		System::getInstance()->getTeams();
?>