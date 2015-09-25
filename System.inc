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
			$result = SQL("SELECT RoundNumber, Player, Role, BestVotes, Statuses.Status from Teams join Players USING(TeamId) join PlayerGame ON(Players.Name = Player) join Games using(GameId) join Statuses on (Games.Status = Statuses.StatusId) where TeamId = ? order by Player, Games.RoundNumber", array($_SESSION['team']))->getAll();
			foreach($result as $obj)
			{
				$stat[$obj['Player']][] = array($obj['Role'], $obj['Status'], $obj['BestVotes']);
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
				$players[$_POST["Player$i"]] = array('Role'=>$_POST["Role$i"], 'BestVotes'=>0,'DressCode'=>$_POST["DressCode$i"],"Surprise"=>0, 'Penalty' => $_POST["Penalty$i"]);
				for ($i = 0; $i < 4; $i++)
					$players[$_POST["BestPlayer$i"]]['BestVotes'] = $_POST["BestVotes$i"];
				foreach($_POST["Surprise"] as $name)
				{	
					if (strlen($name) > 0)
						$players[$name]["Surprise"] = 1;
				}
				foreach ($players as $playerName => $info)
				{
SQL("INSERT INTO `PlayerGame`(`Id`, `Player`,`GameId`,`Role`,`BestVotes`,`DressCode`,`Surprise`,`Penalty`) VALUES (null,?,?,?,?,?,?,?)", array($playerName, $gameId, $info['Role'], $info['BestVotes'], $info['DressCode'], $info["Surprise"], $info['Penalty']));
				}
				getView("HeaderView.inc", null);
			}
		}
	}
}

?>

