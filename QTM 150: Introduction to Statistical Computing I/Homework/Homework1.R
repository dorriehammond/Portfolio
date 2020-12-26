# Homework1
# Student: Dorrie Hammond
# Student ID: 2284917
# THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
# A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Dorrie Hammond

# 0.
LBO <- read.csv("LifetimeBoxOffice.csv")
# 200 Observations, 4 variables
str(LBO)

# 1.
# prints top 10 ranked LifetimeGross movies
# They are already sorted by rank, so there's
# no reason to order them
LBO[1:10,2:3]

# 2.
# prints movies that earned over a billion dollars of LifetimeGross
subset(LBO,subset = LifetimeGross > 1000000000) 

# 3.
# creates subset of LBO containing only movies in 2019
# 13 movies are found in this subset
movies_2019 <- subset(LBO,subset = Year == 2019)
movies_2019

# 4.
# mean and standard deviation of 2019 movies
# mean = 1183262439
# standard deviation = 558485335
mean(movies_2019$LifetimeGross)
sd(movies_2019$LifetimeGross)

# 5.
# This generates a boxplot of the LifetimeGross by Year
# In this case, LifetimeGross is a quantitative value and Year is a 
# categorical value. By displaying the data this way, we can show the trends
# from max, min, and average Lifetime Gross movies from certain years have
# been able to make.  Like a user can see that top movies from 2020
# made a higher average of profit than most of its previous years.
boxplot(LBO$LifetimeGross ~ LBO$Year, main="Lifetime Gross of Top 200 Movies by Year",
        ylab="Lifetime Gross ($)",xlab="Year")

# 6.
y <- c(1,2,1,3,4,1,1,4,2,1,3,4,3,2,1,3,4,1,2,3,1,1,2)
# create factor from y (1,2,3,4), then assign year names as factors, and then ordered=TRUE gives hierarchy
y <- factor(y)
levels(y) <- c("Freshman","Sophomore","Junior","Senior")
y <- factor(y,ordered=TRUE,levels=c("Freshman","Sophomore","Junior","Senior"))
y # print new factor vector with level hierarchy
# proof that Freshman < Sophomore < Junior < Senior is true
y[1] < y[2] # Freshman < Sophomore TRUE
y[2] < y[4] # Sophomore < Junior TRUE
y[4] < y[5] # Junior < Senior TRUE

