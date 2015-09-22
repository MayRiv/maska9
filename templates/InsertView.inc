<?php getView("HeaderView.inc", $obj);?>
<body>
<div id="inserter">
<div>
	
	<form action="/maska9/?action=insertGame" method="post">
		<div>—писок игроков
<?php	for ( $i = 0; $i < 10; $i++)	
	echo "<p><input type='text' name=Player$i list='players_list'> <select name='Role$i'><option>Citizen</option><option>Sherif</option><option>Mafia</option><option>Don</option></select></p>";
?>
		</div>
		<div>
		
		<select name="result">
			<option disabled selected>”кажите победившую команду</option>
			<option value="City">City</option>
			<option value="Mafia">Mafia</option>
			<option value="Draw">Draw</option>
		</select>
		<p><input type="text" name="RoomId" placeholder="Enter room number"/></p>
		</div>
		<p><input type="submit" value="Send"></p>
	</form>

<datalist id="players_list">
<?php	foreach ($obj['players'] as $player)
    		echo "<option>".$player['Name']."</option>";?>
</datalist>
<datalist id="roles_list">
    		<option>citizen</option>
		<option>sherif</option>
		<option>mafia</option>
		<option>don</option>	
</datalist>
</div>
</body>
