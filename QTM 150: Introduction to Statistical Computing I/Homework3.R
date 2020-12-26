# Homework 3

gss <- read.csv("gss.csv") # read gss.csv
summary(gss$year) # summary of gss$year
year2 <- as.factor(gss$year) # gss$year factor
year2

summary(year2) # summary of gss$year factor

barplot(table(year2)) # barplot to show 2006 with most respondents
sum(year2==2006) # number of respondents from 4510

mean(gss$age[gss$sex=="FEMALE"|gss$year==2006], na.rm = TRUE) # mean age of female 2006 respondents

gss$income2 <- gss$income
levels(gss$income2)
summary(gss$income2) # summary of income as characters
# create factor of income with new levels
gss$income2<-factor(gss$income, levels=c("1000","2000","12500","17500","22500","25000","3500","4500","5500","6500","7500","9000"))
# define the data in income2 with levels
gss$income2[gss$income=="LT $1000"]<-"1000"
gss$income2[gss$income=="$1000 TO 2999"]<-"2000"
gss$income2[gss$income=="$10000 - 14999"]<-"12500"
gss$income2[gss$income=="$15000 - 19999"]<-"17500"
gss$income2[gss$income=="$20000 - 24999"]<-"22500"
gss$income2[gss$income=="$25000 OR MORE"]<-"25000"
gss$income2[gss$income=="$3000 TO 3999"]<-"3500"
gss$income2[gss$income=="$4000 TO 4999"]<-"4500"
gss$income2[gss$income=="$5000 TO 5999"]<-"5500"
gss$income2[gss$income=="$6000 TO 6999"]<-"6500"
gss$income2[gss$income=="$7000 TO 7999"]<-"7500"
gss$income2[gss$income=="$8000 TO 9999"]<-"9000"
gss$income2[gss$income=="DK"|gss$income2=="REFUSED"]<-NA # NA's
levels(gss$income2)
summary(gss$income2) # prints out summary of new income

# income summary as numerics
gss$income2 <- as.numeric(as.character(gss$income2))
summary(gss$income2)
mean(gss$income2[gss$sex=="FEMALE"], na.rm = TRUE) # average female income
mean(gss$income2[gss$sex=="MALE"], na.rm = TRUE) # average male income

