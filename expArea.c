
def na = Double.NaN;
def bn = BarNumber();
def lastbar = !IsNaN(close[0]) and IsNaN(close[-1]);
def lastbarbn = if lastbar then bn else lastbarbn[1];

input formula_bars = 50;

# ref signal , close of last bar
def lastcls = if lastbar then close
 else if (bn < lastbarbn or bn > (lastbarbn + formula_bars)) then na
 else lastcls[1];

input plot_horz_line_after = yes;
plot z1 = if plot_horz_line_after then lastcls else na;
z1.SetDefaultColor(Color.GRAY);

def start_count = 1;
# counting numbers for formula , 1 to curve_bars
def cnt = if (bn <= lastbarbn or bn > (lastbarbn + formula_bars)) then na
  else if bn == (lastbarbn + 1) then start_count
  else (cnt[1] + 1);


# ////////////////////////////////////////
#  test formula 1

# start with the sin example
input amplitude_factor = 0.8;
input periodBars = 16;
def angle = 2 * Double.Pi / periodBars;

# replace my formula , with your formula.
#   baseline - equal to the close of the last bar
#   cnt - a counter with valid #'s, only during the desired bar range, 1 to formula_bars
def formula1 = lastcls + (amplitude_factor * Sin(angle * cnt));

plot f1 = formula1;
f1.SetDefaultColor(Color.CYAN);
# f1.SetStyle(Curve.MEDIUM_DASH);
f1.HideBubble();
# ////////////////////////////////////////


# ////////////////////////////////////////
#  test formula 2
# plot a line with a random number added to the previous value
# % range  -1.5% to 1.5% of prev , added to prev
input formula2_per = 1.5;
def rand = ( (2 * formula2_per / 100) * Random()) - (formula2_per / 100);

def start2 = lastcls;
# change the 3rd line of this formula to your formula
def formula2 =  if (bn < lastbarbn or bn > (lastbarbn + formula_bars)) then na
  else if  bn == (lastbarbn + 1) then start2
    else (formula2[1] + (formula2[1] * rand));

plot f2 = formula2;
f2.SetDefaultColor(Color.MAGENTA);
# f2.SetStyle(Curve.MEDIUM_DASH);
f2.HideBubble();
# ////////////////////////////////////////


# ////////////////////////////////////////
#  test formula 3
# plot line that has same slope as the slope between the last 2 bars
def slope = if bn < lastbarbn then na
 else if lastbar then (close - close[1] )
 else slope[1];

def formula3 = if (bn < lastbarbn or bn > (lastbarbn + formula_bars)) then na
  else if  bn == (lastbarbn) then close
    else (formula3[1] + slope);

plot f3 = formula3;
f3.SetDefaultColor(Color.YELLOW);
# f2.SetStyle(Curve.MEDIUM_DASH);
f3.HideBubble();
# ////////////////////////////////////////


# ////////////////////////////////////////
#  test formula 4
# curve
input slopefactor = 0.024;
def formula4 = if (bn < lastbarbn or bn > (lastbarbn + formula_bars)) then na
  else if  bn == (lastbarbn) then close
    else (formula4[1] + (cnt * slope * slopefactor));

plot f4 = formula4;
f4.SetDefaultColor(Color.green);
# f2.SetStyle(Curve.MEDIUM_DASH);
f4.HideBubble();
# ////////////////////////////////////////


# --------------------------------------------

input test2_bn_label = yes;
AddLabel(test2_bn_label, " bar# after last bar " + (lastbarbn + 1), Color.CYAN);
AddLabel(test2_bn_label, "+ formula_bars: " + formula_bars, Color.CYAN);
AddLabel(test2_bn_label, " to " + (lastbarbn + formula_bars), Color.CYAN);

#addchartbubble(1,70,rand, color.cyan, no);

input test1_bn_bubbles = no;
AddChartBubble(test1_bn_bubbles and !IsNaN(cnt), lastcls, bn , Color.CYAN, no);
