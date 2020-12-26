library(ggplot2) # load ggplot2 package first

?txhousing # more information about the data set
str(txhousing) # structure of txhousing

# 1.
txhousing_San_Antonio <- subset(txhousing, txhousing$city=="San Antonio")

# 2/3.
ggplot(data=txhousing_San_Antonio, aes(x=year, y=median)) +
  geom_bar(stat="identity", fill="steelblue") +
  labs(x="Year",y="Median Income ($)",title="Median Income in San Antonio, TX by Year")+
  theme_bw()

# 4.
txhousing_Austin <- subset(txhousing, txhousing$city=="Austin")
ggplot(data=txhousing_Austin, aes(x=year, y=median)) +
  geom_bar(stat="identity", fill="skyblue") +
  labs(x="Year",y="Median Income ($)",title="Median Income in Austin, TX by Year")+
  theme_bw()

# 5.
txhousing_Two_Cities <- subset(txhousing, txhousing$city=="San Antonio"|txhousing$city=="Austin")
ggplot(data=txhousing_Two_Cities,aes(x=year,y=median,fill=city)) +
  geom_bar(stat="identity",position = position_dodge()) +
  labs(x="Year",y="Median Income ($)",title="Median Income in Austin, TX vs. San Antonio, TX by Year") +
  scale_fill_brewer(palette="Paired") +
  theme_bw()
