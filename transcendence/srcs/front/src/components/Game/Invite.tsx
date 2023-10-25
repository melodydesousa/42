
let invite:boolean = false;

export const setInvite = (state:boolean) =>
{
	invite = state;
}

export const checkInvite = () =>
{
	return (invite);
}