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
		session_start();
		if ($_SESSION['authorizedCaptain'] <>1) 
		{
			header("Location: /maska9/authCaptain.php");
		}
		else
		{
			$stat = array();
			$result = SQL("SELECT RoundNumber, Player, Role, Statuses.Status from Teams join Players USING(TeamId) join PlayerGame ON(Players.Name = Player) join Games using(GameId) join Statuses on (Games.Status = Statuses.StatusId) where TeamId = ? order by Player, Games.RoundNumber", array($_SESSION['team']))->getAll();
			foreach($result as $obj)
			{
				$stat[$obj['Player']] = array($obj['Role'], $obj['Status']);
			}
			getView("TeamsView.inc", $stat);
		}
	}

	public function getGames()
	{

	}
	public function insertGame()
	{
		session_start();
		if ($_SESSION['authorizedAdmin'] <>1) 
		{
			header("Location: /maska9/authAdmin.php");
		}
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("SELECT * FROM Players")->getAll();
				$obj = array('players'=> $players);
				getView("InsertView.inc",$obj);
			}
			else
			{
				$roomId = 1;
				$masterId = SQL("select masterId from Masters where masterName like ?", array($_POST['Master']))->getAll()[0]['masterId'];
				$result = $_POST['result'];
				$status = SQL("select StatusId from Statuses where Status like ?", array($result))->getAll()[0]['StatusId'];
				$gameId = SQL("select max(GameId) as m from Games")->getAll()[0]['m'];
				SQL("insert into Games (`GameId`,`RoomId`,`Status`,`MasterId`, `RoundNumber`) values (?,?,?,?,?)", array($gameId+1,$roomId, $status, $masterId, $_POST['RoundNumber']));
				$players = array();
				for ($i = 0; $i < 10; $i++)
				$players[$_POST["Player$i"]] = $_POST["Role$i"];
				foreach ($players as $playerName => $playerRole)
    					SQL("insert into PlayerGame (Player,GameId,Role) values (?,?,?)", array($playerName, $gameId , $playerRole ));
				echo "<a href=\"/maska9/?action=insertGame\">Insert another game</a>";
			}
		}
	}
}

?>

