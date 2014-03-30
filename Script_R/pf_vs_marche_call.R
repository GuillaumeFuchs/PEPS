past <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/past.txt");
risk <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/risk.txt");
risk_free <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/risk_free.txt");
total <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/total.txt");
trade <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/trade.txt");

#par(mfrow=c(1,2));
plot(c(0, 1), c(min(min(total, min(risk, risk_free)), past), max(max(total, max(risk, risk_free)), past)) , type="n", xlab="Time", ylab="Value");
lines(seq(0, 1, 0.002), past, col="black");
lines(seq(0, 1, 0.002), risk_free, col="blue");
lines(seq(0, 1, 0.002), risk, col="red");
lines(seq(0, 1, 0.002), total, col="purple");
abline(h=100);
abline(h=0);

#cols <- c("red", "blue")[(trade>0)+1];
#barplot(trade, col=cols, ylim=c(min(trade), max(trade)),xlab="Time", ylab="Trade");
