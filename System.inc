<?php
class System 
{
	private static $_instance;
	public static  function getInstance()
	{
		if (System::$_instance == null) System::$_instance = new System();
		return System::$_instance;
	}

	private function __construct()
	{
		# code...
	}
	public function getPlayers()
	{
		$players = SQL("SELECT * FROM Players")->getAll();
		getView("PlayersView.inc",$players);
	}

	public function getTeams()
	{

	}

	public function getGames()
	{

	}
	public function insertGame()
	{
		session_start();
		if ($_SESSION['authorized'] <>1) 
		{
			header("Location: /maska9/auth.php");
		}
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("SELECT * FROM Players")->getAll();
				$obj = array('id'=>$_SESSION['id'], 'players'=> $players);
				getView("InsertView.inc",$obj);
			}
			else
			{
				echo 'players are: ';
				foreach ($_POST['Player'] as $player)
    					echo $player." ";
				echo "\nSucces! <a href=\"/maska9/?action=insertGame\">Insert another game</a>";
			}
		}
	}
}

?>

