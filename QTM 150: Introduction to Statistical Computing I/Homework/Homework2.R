# Homework2

# 0.
gss <- read.csv("gss.csv")

# 1.
sum(is.na(gss$marital))

# 2.
female <- length(subset(gss$sex,subset = gss$sex == "FEMALE")) / length(gss$sex) * 100
female
male <- length(subset(gss$sex,subset = gss$sex == "MALE")) / length(gss$sex) * 100
male

# 3.
length(na.omit(subset(gss$age, gss$age > 29 & gss$age < 41))) / length(na.omit(gss$age)) * 100

# 4.
gss_08_10 <- subset(gss,gss$year == 2008 | gss$year == 2010)
sum(na.omit(gss_08_10$age)) / length(na.omit(gss_08_10$age))
