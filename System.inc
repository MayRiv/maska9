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
	public function getPlacing()
	{
		$placing = null;
		if (isset($_GET['round']))
		{
			$placing = (int)$_GET['round'];
		}
		getView("PlacingView.inc", $placing);
	}
	public function showGames()
	{
		session_start();
		if ($_SESSION['authorizedAdmin'] <>1) 
		{
			header("Location: /authAdmin.php");
		}
		else
		{
			if (!isset($_GET['gameid']) || isset($_GET['delete']))
			{
				if (isset($_GET['delete']))
				{
					$gameid = $_GET['gameid'];
					SQL("delete from PlayerGame where gameid=?", array($gameid));
					SQL("delete from BestPlayersNominated where gameid=?", array($gameid));
					SQL("delete from MasterGame where gameid=?", array($gameid));
					SQL("delete from Games where gameid=?", array($gameid));
				}
				$res = SQL("select gameId,roomId, RoundNumber, MasterName, Statuses.Status from Games join Masters USING(masterId) join Statuses ON(StatusId=Games.Status) order by roundNumber ASC, roomId", null)->getAll();
				foreach($res as $game)
				{
					$games[$game['RoundNumber']][$game['roomId']] = array($game['MasterName'], $game['Status'], $game['gameId']);
				}
 				getView("showGamesView.inc", $games);

			}
			else
			{
			
				$game = SQL("select MasterName, Statuses.Status, roomId from Games join Masters using(masterId) join Statuses on(Statuses.StatusId=Games.Status) where gameid=?", array($_GET['gameid']))->getAll()[0];
				$players = SQL("select Penalty,player, Role, DressCode, BestMove, BestVotes, Surprise from PlayerGame where gameid=?",array($_GET['gameid']))->getAll();
				$packed = array('game'=>$game, 'players'=>$players);
				getView("GameView.inc", $packed);
			}
		}
	}
	public function getAdminPanel()
	{
		session_start();
		if ($_SESSION['authorizedAdmin'] <>1) 
		{
			header("Location: maska9/authAdmin.php");
		}
		else
		{
			$objects = null;
			if (isset($_GET['players']))
			{
				$players = SQL("Select player,SUM(Role) + SUM(BestMove) + SUM(BestVotes) - SUM(Penalty) as points from PlayerGame group by player order by points DESC", null)->getAll();
				$objects = array("title"=>"player", 'list'=>$players);
			}
			if (isset($_GET['teams']))
			{
				$teams = SQL("select team, SUM(p) as points from (SELECT Teams.Name as team, Role + BestMove + BestVotes - Penalty AS p
FROM PlayerGame
JOIN Players ON ( Players.Name = PlayerGame.player ) 
JOIN Teams
USING ( teamid ) 
GROUP BY player) t group by team order by points DESC", null)->getAll();
				$objects = array("title"=>"team", 'list'=>$teams);
			}
			if (isset($_GET['masters']))
			{
				$masters = SQL("select masterName as masters, SUM(Votes) points from MasterGame join Masters USING(masterId) group by masterId order by points DESC", null)->getAll();
				$objects = array("title"=>"masters", 'list'=>$masters);
			}
			if (isset($_GET['best']))
			{
				$players = SQL("select v1.player,  points  as rating, votes FROM (select player, count(*) as points from BestPlayersNominated GROUP by player) as v1 JOIN (select player, SUM(`PlayerGame`.`BestVotes`) as votes from PlayerGame group by player) as v2 on(v1.player = v2.player) order by rating DESC, votes DESC", null)->getAll();
				for($i = 0; $i < count($players); $i++)
				{
					$players[$i]['points'] = $players[$i]['rating'] . "(".$players[$i]['votes'].")";
				}
				$objects = array("title"=>"player", 'list'=>$players);
			
			}
			if (isset($_GET['dressm']))
			{
				$players = SQL("select player, SUM(dresscode) as points from PlayerGame join Players on(player=name) where isMale=true group by player order by points desc", null)->getAll();
				$objects = array("title"=>"player", 'list'=>$players);
			}
			if (isset($_GET['dressw']))
			{
				$players = SQL("select player, SUM(dresscode) as points from PlayerGame join Players on(player=name) where isMale=0 group by player order by points desc", null)->getAll();
				$objects = array("title"=>"player", 'list'=>$players);
			}
			if (isset($_GET['dresst']))
			{
				$players = SQL("select team, SUM(p) as points from (SELECT Teams.Name as team, SUM(dresscode) AS p
FROM PlayerGame
JOIN Players ON ( Players.Name = PlayerGame.player ) 
JOIN Teams
USING ( teamid ) 
GROUP BY player) t group by team order by points DESC", null)->getAll();
				$objects = array("title"=>"team", 'list'=>$players);
			}
			if (isset($_GET['surprise']))
			{
				$players = SQL("select player, SUM(surprise) as points from PlayerGame group by player order by points DESC", null)->getAll();
				$objects = array("title"=>"player", 'list'=>$players);
			}

			getView("adminPanelView.inc",$objects);
		}
	}
	public function getPlayers()
	{
		$players = SQL("SELECT * FROM Players")->getAll();
		$masters = SQL("SELECT * FROM Masters")->getAll();
		var_dump($masters);
		getView("PlayersView.inc",array($players, $masters));
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
			$result = SQL("SELECT RoundNumber, Player, Role, BestVotes, BestMove, Statuses.Status from Teams join Players USING(TeamId) join PlayerGame ON(Players.Name = Player) join Games using(GameId) join Statuses on (Games.Status = Statuses.StatusId) where TeamId = ? order by Player, Games.RoundNumber", array($_SESSION['team']))->getAll();
			foreach($result as $obj)
			{
				$stat[$obj['Player']][] = array($obj['Role'], $obj['BestMove'], $obj['BestVotes']);
			}
			$sum = array();
			foreach($stat as $player=>$info)
			{	
				$sum[$player] = 0;
				foreach($info as $game)
				{
					$sum[$player] += $game[0] + $game[1] + $game[2];
				}
			}
			$packed = array('sum'=>$sum, 'stat'=>$stat);
			getView("TeamsView.inc", $packed);
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
				$masters = SQL("SELECT * FROM Masters")->getAll();
				$obj = array('players'=> $players, 'masters'=>$masters);
				getView("InsertView.inc",$obj);
			}
			else
			{
				$roomId = $_POST['RoomId'];
				$masterId = SQL("select masterId from Masters where masterName like ?", array($_POST['Master']))->getAll()[0]['masterId'];
				$result = $_POST['result'];
				$status = SQL("select StatusId from Statuses where Status like ?", array($result))->getAll()[0]['StatusId'];
				$gameId = SQL("select max(GameId) as m from Games")->getAll()[0]['m'] + 1;
				
				
				SQL("insert into Games (`GameId`,`RoomId`,`Status`,`MasterId`, `RoundNumber`) values (?,?,?,?,?)", array($gameId,$roomId, $status, $masterId, $_POST['RoundNumber']));

				$masterMark = 0;
				foreach($_POST['MasterMark'] as $mark)
				{
					$masterMark += $mark;
				}
				SQL("insert into `MasterGame`(`MasterId`, `GameId`, `Votes`) VALUES (?,?,?)", array($masterId, $gameId, $masterMark));
				$players = array();
				for ($i = 0; $i < 10; $i++)
				$players[$_POST["Player$i"]] = array('Role'=>$_POST["Role$i"], 'BestVotes'=>0, 'BestMove'=> 0, 'DressCode'=>$_POST["DressCode$i"],"Surprise"=>0, 'Penalty' => $_POST["Penalty$i"]);
				$players[$_POST['BestMovePlayer']]['BestMove'] = $_POST['BestMovePoints'];
				
				for ($i = 0; $i <= 4; $i++)
				{
					$players[$_POST["BestPlayer$i"]]['BestVotes'] = $_POST["BestVotes$i"];
					if (strlen($_POST["BestPlayer$i"]) > 0)
SQL("insert into `BestPlayersNominated`(`player`, `gameId`) values (?,?)", array($_POST["BestPlayer$i"],$gameId));
				}
				foreach($_POST["Surprise"] as $name)
				{	
					if (strlen($name) > 0)
						$players[$name]["Surprise"] = 1;
				}
				foreach ($players as $playerName => $info)
				{
					
					$rolePoints = 0;
					if ($_POST['result'] === "City")
					{
						if ($info['Role'] === "Citizen" || $info['Role'] === "Sherif")
							$rolePoints = 15;
					}
					if ($_POST['result'] === "Mafia")
					{
						if ($info['Role'] === "Don" || $info['Role'] === "Mafia")
							$rolePoints = 15;
					}
SQL("INSERT INTO `PlayerGame`(`Id`, `Player`,`GameId`,`Role`,`BestVotes`,`BestMove`,`DressCode`,`Surprise`,`Penalty`) VALUES (null,?,?,?,?,?,?,?,?)", array($playerName, $gameId, $rolePoints, $info['BestVotes'], $info['BestMove'], $info['DressCode'], $info["Surprise"], $info['Penalty']));
				}
				getView("HeaderView.inc", null);
			}
		}
	}
}

?>