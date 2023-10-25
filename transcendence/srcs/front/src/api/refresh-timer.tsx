let refreshTimer: any;

export const startRefreshTimer = (refresh: any) => {
	refreshTimer = setInterval(async () => {
		try {
			await refresh();
		} catch (error) {
			console.log("Token refresh failed:", error);
		}
	}, 13 * 60 * 1000);
};

export const stopRefreshTimer = () => {
	clearInterval(refreshTimer);
};
