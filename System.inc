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
				$roomId = 1;
				$masterId = $_SESSION['id'];
				$result = $_POST['result'];
				echo $result;
				$status = SQL("select StatusId from Statuses where Status like ?", array($result))->getAll()[0]['StatusId'];
				$gameId = SQL("select max(GameId) as m from Games")->getAll()[0]['m'];
				SQL("insert into Games (`GameId`,`RoomId`,`Status`,`MasterId`) values (?,?,?,?)", array($gameId+1,$roomId, $status, $masterId));
				$players = array();
				for ($i = 0; $i < 10; $i++)
				$players[$_POST["Player$i"]] = $_POST["Role$i"];
				foreach ($players as $playerName => $playerRole)
    					SQL("insert into PlayerGame (Player,GameId,RoleId) values (?,?,?)", array($playerName, $gameId , $playerRole ));
				echo "<a href=\"/maska9/?action=insertGame\">Insert another game</a>";
			}
		}
	}
}

?>

