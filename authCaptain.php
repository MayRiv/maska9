<?php
	require("viewer.inc");
	require("DBManager.inc");
	$host = "mysql.hostinger.com.ua";
	$dbName = "u558605037_maska";
	$user = "u558605037_maska";
	$password = "starmaf";

	
	$passwordAdmin = "4efe3aff7e691264809e8e65282c96d0";
	if ($_SERVER['REQUEST_METHOD'] == 'POST')
	{
		session_start();
		DBManager::getInstance()->connect($host, $dbName, $user, $password);
		$result = SQL("Select password from Teams where TeamId = ?", array($_POST['Team']))->getAll()[0];
		if (MD5($_POST['Pass']) === $result['password'] ||
		    MD5($_POST['Pass']) === $passwordAdmin)
		{		
			$_SESSION['authorizedCaptain'] = 1;
			$_SESSION['team'] = $_POST['Team'];
			header("Location: /?action=getTeams");
		}
		else echo "Wrong password or login";
	}
	else
		getView("AuthCaptainView.inc",NULL);

?>