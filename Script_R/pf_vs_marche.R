pf_simul <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/testPeps/Data/couv_simulation.txt");
past <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/testPeps/Data/past.txt");
delta <- scan("C:/Users/Fuchsg/Documents/GitHub/PEPS/testPeps/testPeps/Data/delta_simulation.txt");

pf_simul = -pf_simul;
par(mfrow=c(1,2));
plot(c(0, 1), c(min(min(past), min(pf_simul)), max(max(past), max(pf_simul))), type="n", xlab="Time", ylab="Value");
lines(seq(0, 1, 0.001), past, col="red");
lines(seq(0, 1, 0.001), pf_simul, col="blue");
legend('bottomleft', c("Valeur marché", "Valeur portefeuille"), lty=c(1,1), col=c("red", "blue"), text.width=0.15);
abline(h=100);
plot(c(0, 1), c(0, 1), type="n", xlab="Time", ylab="Valeur delta");
lines(seq(0, 1, 0.001), delta);
legend('bottomleft', c("Valeur marché"), lty=c(1), col=c("black"), text.width=0.15);