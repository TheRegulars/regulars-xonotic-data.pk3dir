entity autorebalance_ent;

AUTOCVAR(g_autorebalance_timeout, int, -1, "Default timeout after teams become unbalanced");

void Autorebalance_Init() {
	autorebalance_ent = spawn();
	setthink(autorebalance_ent, Autorebalance_Call);
}

void Autorebalance_Schedule() {
	if (autocvar_g_autorebalance_timeout <= 0 || !teamplay || warmup_stage || game_stopped)
		return;

	autorebalance_ent.nextthink = time + autocvar_g_autorebalance_timeout + 1;
}

void Autorebalance_Call(entity autorebalance_ent) {
	if (autocvar_g_autorebalance_timeout <= 0 || !teamplay || warmup_stage || game_stopped)
		return;

	entity balance = TeamBalance_CheckAllowedTeams(NULL);
	TeamBalance_GetTeamCounts(balance, NULL);
	int min_players, max_players, players;
	min_players = FLOAT_MAX;
	max_players = 0;
	for (int i = 1; i <= NUM_TEAMS; ++i)
	{
		players = TeamBalance_GetNumberOfPlayers(balance, i);
		if (players < 0)
			continue;

		if (players < min_players)
			min_players = players;

		if (players > max_players)
			max_players = players;
	}
	if ((max_players - min_players) > 1) {
		LOG_INFOF("Min team: %d, max team: %d, calling autorebalance", min_players, max_players);
		Autorebalance_Fix();
	}

	TeamBalance_Destroy(balance);
}

void Autorebalance_SendClientCvar(entity client) {
	stuffcmd(client, sprintf("set _autorebalance_timeout %d\n", autocvar_g_autorebalance_timeout));
}

void Autorebalance_Fix() {
	autorebalance();

    FOREACH_CLIENTSLOT(true,
    {
        if(IS_REAL_CLIENT(it))
            sprint(it, "\{1}^3Teams was rebalanced automatically\n");
    });
}
