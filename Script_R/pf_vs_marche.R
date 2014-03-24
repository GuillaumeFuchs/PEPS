pf <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/testPeps/Data/couv_simulation.txt");
past <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/testPeps/Data/past.txt");
trade <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/testPeps/Data/delta_simulation.txt");

pf = -pf;
par(mfrow=c(1,2));
plot(c(0, 1), c(min(min(past), min(pf)), max(max(past), max(pf))), type="n", xlab="Time", ylab="Value");
lines(seq(0, 1, 0.01), past, col="red");
lines(seq(0, 1, 0.01), pf, col="blue");
legend('bottomleft', c("Valeur marché", "Valeur portefeuille"), lty=c(1,1), col=c("red", "blue"), text.width=0.15);
abline(h=100);
cols <- c("red", "blue")[(trade>0)+1]
barplot(trade, col=cols, ylim=c(-35,35),xlab="Time", ylab="Valeur actif acheté");
