<?php getView("HeaderView.inc", $obj);?>
<body>
<div id="inserter">
<div>
	
	<form action="/maska9/?action=insertGame" method="post">
		<div>
		<p><input type='text' name="Master" placeholder="Ник ведущего"></p>
		<p><input type='text' name="RoundNumber" placeholder="Номер раунда"></p>			
		Список игроков      Роль Оценка ведущего
<?php	for ( $i = 0; $i < 10; $i++)	
	echo "<p><input type='text' name=Player$i list='players_list'>
		<select name='Role$i'>
			<option>Citizen</option>
			<option>Sherif</option>
			<option>Mafia</option>
			<option>Don</option>
		</select>
		<input type='text' name='MasterMark'/>
</p>";
?>
		</div>
		<div>
		<div>
		<p>Голосование за лучшего игрока. Оставьте пустой строчку, если кандидатов меньше 4.</p>
<?php	for ( $i = 0; $i < 4; $i++) 
			echo "<p><input type='text' name='BestPlayer$i' placeholder='Ник игрока' list='players_list'/><input type='text' name='BestPoints$i' placeholder='Количество голосов'/></p>";
?>
		</div>
		
			<select name="result">
				<option disabled selected>Укажите победившую команду</option>
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
