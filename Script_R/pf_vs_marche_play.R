s1 <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/s1.txt");
s2 <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/s2.txt");
s3 <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/s3.txt");
s4 <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/s4.txt");

d1 <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/d1.txt");
d2 <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/d2.txt");
d3 <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/d3.txt");
d4 <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/d4.txt");

price <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/price.txt");

risk <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/risk.txt");
risk_free <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/risk_free.txt");
total <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/Data/total.txt");

#par(mfrow=c(1,2));
min_y = min(min(min(min(min(min(min(min(min(min(min(s1, s2), s3), s4), d1), d2), d3), d4), price), risk), risk_free), total)
max_y = max(max(max(max(max(max(max(max(max(max(max(s1, s2), s3), s4), d1), d2), d3), d4), price), risk), risk_free), total)

plot(c(0, 6), c(min_y, max_y) , type="n", xlab="Time", ylab="Value");

lines(seq(0, 6, 0.02), s1, col="yellow");
lines(seq(0, 6, 0.02), s2, col="coral");
lines(seq(0, 6, 0.02), s3, col="chocolate");
lines(seq(0, 6, 0.02), s4, col="orange");

lines(seq(0, 6, 0.02), risk_free, col="blue");
lines(seq(0, 6, 0.02), risk, col="red");
lines(seq(0, 6, 0.02), total, col="purple");
abline(h=110, lty=3);
abline(h=120, lty=3);
abline(h=0, lty=3);

#cols <- c("red", "blue")[(trade>0)+1];
#barplot(trade, col=cols, ylim=c(min(trade), max(trade)),xlab="Time", ylab="Trade");
