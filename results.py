import numpy as np
import pandas as pd

def create_drawdowns(equity_curve):
    """
    Calculate the largest peak-to-trough drawdown of the PnL curve
    as well as the duration of the drawdown. Requires that the 
    pnl_returns is a pandas Series.

    Parameters:
    pnl - A pandas Series representing period percentage returns.

    Returns:
    drawdown, duration - Highest peak-to-trough drawdown and duration.
    """

    # Calculate the cumulative returns curve 
    # and set up the High Water Mark
    # Then create the drawdown and duration series
    hwm = [0]
    eq_idx = equity_curve.index
    drawdown = pd.Series(index = eq_idx)
    duration = pd.Series(index = eq_idx)

    # Loop over the index range
    for t in range(1, len(eq_idx)):
        cur_hwm = max(hwm[t-1], equity_curve[t])
        hwm.append(cur_hwm)
        drawdown[t]= hwm[t] - equity_curve[t]
        duration[t]= 0 if drawdown[t] == 0 else duration[t-1] + 1
    return drawdown.max(), duration.max()

def annualised_sharpe(returns, N=252):
	"""
	Calculate the annualised Sharpe ratio of a returns stream 
	based on a number of trading periods, N. N defaults to 252,
	which then assumes a stream of daily returns.
	The function assumes that the returns are the excess of 
	those compared to a benchmark.
	"""
	return np.sqrt(N) * returns.mean() / returns.std()

pdf = pd.read_csv("amstockchart/data/portfolio.csv")

pdf['daily_ret'] = pdf['Value'].pct_change()
# Assume an average annual risk-free rate over the period of 5%
pdf['excess_daily_ret'] = pdf['daily_ret'] - 0.05/252
pdf['equity_daily_ret'] = (1.0 + pdf['daily_ret']).cumprod()
print pdf
pdf.set_index('Date', inplace=True)
print "total return: " + str(pdf['equity_daily_ret'][-1])
print "annually daily_ret sharpe ratio: " + str(annualised_sharpe(pdf['daily_ret']))
print "annually excess_daily_ret sharpe ratio: " + str(annualised_sharpe(pdf['excess_daily_ret']))
print "max draw down: " + str(create_drawdowns(pdf['daily_ret']))

print "done!"