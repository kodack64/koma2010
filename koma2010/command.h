#pragma once

enum CommandKind{
	OnLeft,
	OnRight,
	OnDown,
	OnDash,
	OffLeft,
	OffRight,
	OffDown,
	OffDash,
	OnJump
};

struct Command{
	CommandKind mycom;
	int myframe;
	int nextframe;
};
