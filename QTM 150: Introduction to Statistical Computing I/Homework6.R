library(ggplot2) # load ggplot2 package first
library(dplyr) # load dplyr package first

newgss2 <- read.csv("newgss2.csv", stringsAsFactors = TRUE) #import data set

#1
married_age <- newgss2 %>% 
  group_by(year) %>% 
  summarize(avg_age=mean(age,na.rm=T),per_mar=mean(marital=="MARRIED",na.rm=T)*100)
married_age

#2
ggplot(married_age,aes(x=year,y=per_mar)) +
  geom_bar(stat="identity", fill="skyblue") +
  labs(x="Year", y="Percent of Married Respondents", title="Percent of Married Respondents by Year")

#4
income_party <- newgss2 %>% group_by(year) %>%
  filter(partyid=="STRONG DEMOCRAT",year>=2000) %>%
  summarize(per=mean(income=="$25000 OR MORE",na.rm=T)*100,party="dem")
  
repgss <- newgss2 %>% group_by(year) %>%
  filter(partyid=="STRONG REPUBLICAN",year>=2000) %>%
  summarize(per=mean(income=="$25000 OR MORE",na.rm=T)*100,party="rep")

indgss <- newgss2 %>% group_by(year) %>%
  filter(partyid=="INDEPENDENT",year>=2000) %>%
  summarize(per=mean(income=="$25000 OR MORE",na.rm=T)*100,party="ind")

income_party <- rbind(income_party,repgss)
income_party <- rbind(income_party,indgss)

#5
ggplot(income_party,aes(x=year,y=per,fill=party)) +
  geom_bar(stat="identity", position=position_dodge())+
  labs(x="Year", y="Percent of Respondents", title="Percent of Respondents with Income +$25000 by Party")

#7
ave_incomes <- newgss2 %>%
  group_by(year,region) %>%
  summarize(average=mean(income1,na.rm=T))

ave_incomes %>% group_by(year) %>%
  arrange(average) %>%
  summarize(richest=last(region),poorest=first(region))
  
  
  
  
  
  
  
