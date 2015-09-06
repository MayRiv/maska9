<?php
	require("viewer.inc");
	require("DBManager.inc");
	$host = "localhost";
	$dbName = "maska9";
	$user = "root";
	$password = "";
	if ($_SERVER['REQUEST_METHOD'] == 'POST')
	{
		session_start();
		DBManager::getInstance()->connect($host, $dbName, $user, $password);
		$masters = SQL("Select MasterId from Masters where MasterName like ? AND MasterPass = ?",array($_POST['Name'], MD5($_POST["Pass"])))->getAll();
		if (count($masters) > 0)
		{		
			echo "test";
			$_SESSION['authorized'] = 1;
			$_SESSION['id'] = $masters[0]['MasterId'];
			header("Location: /maska9/?action=insertGame");
		}
		else echo "Wrong password or login";
	}
	else
		getView("AuthView.inc",NULL);

?>
