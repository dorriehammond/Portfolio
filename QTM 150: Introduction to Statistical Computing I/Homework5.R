library(ggplot2) # load ggplot2 package first

gss2k <- read.csv("gss2k.csv", stringsAsFactors = TRUE) #import data set

table(gss2k$degree,exclude = NA)
table(gss2k$sex,gss2k$degree)

ggplot(gss2k, aes(degree))+
  geom_bar() +
  labs(x="Level of Education", y="Total Participants", title="Frequency of Degrees by Sex")

ggplot(subset(gss2k,!is.na(degree)), aes(degree))+
  geom_bar() +
  labs(x="Level of Education", y="Total Participants", title="Frequency of Degrees by Sex")

ggplot(subset(gss2k,!is.na(degree)), aes(degree))+
  geom_bar(aes(fill=sex)) +
  labs(x="Level of Education", y="Total Participants", title="Frequency of Degrees by Sex")

ggplot(subset(gss2k,!is.na(degree)),aes(degree)) +
  geom_bar(aes(fill=sex),position = position_dodge()) +
  labs(x="Level of Education", y="Total Participants", title="Frequency of Degrees by Sex")

ggplot(subset(gss2k,!is.na(health)&health!="DK"),aes(x=health,y=age))+
  geom_boxplot() +
  facet_grid(~sex)










