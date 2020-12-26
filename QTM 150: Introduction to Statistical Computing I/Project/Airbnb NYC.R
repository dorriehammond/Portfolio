library(ggplot2)
library(dplyr)
library(tidyverse)
library(leaflet)
library(stringr)
library(sf)
library(mapview)
library(htmlwidgets)
library(webshot)
library(tigris)
library(sp)
library(maptools)
library(broom)
library(httr)
library(rgdal)

AIRBnB <- read.csv("AIRBnB_NYC.csv")

summary(AIRBnB$price)
sd(AIRBnB$price, na.rm = T)
ggplot(AIRBnB, aes(price, na.rm = T)) + 
  geom_histogram(aes(y = ..density..),fill = "green", col= "red", alpha = 0.2) +
  labs(title="Price Distribution for AirBnB Listings")

AIRBnB <- AIRBnB %>% filter(room_type=="Entire home/apt")

AIRBnB_pricekeep <- AIRBnB %>% filter(price<=350)

ggplot(AIRBnB_pricekeep, aes(price, na.rm = T)) + 
  geom_histogram(aes(y = ..density..),fill = "green", col= "red", alpha = 0.2) +
  labs(title="Price Distribution for Entire Home/Apartment Listings from $0-$350")

AIRBnB <- AIRBnB %>% filter(price<=350)

summary(AIRBnB$longitude)
summary(AIRBnB$latitude)
ggplot(AIRBnB, aes(x=longitude,y=latitude)) + 
  geom_point() + labs(x="Latitude", y="Longitude", title="Map of AirBnB Listings in NYC")

ggplot(AIRBnB, aes(neighbourhood_group)) + 
  geom_bar() +
  labs(x="NYC Neighbourhood Groups", y="Number of Listings", title="Density of Listings for Each Area of NYC")

AIRBnB <- AIRBnB %>% filter(neighbourhood_group=="Manhattan"|neighbourhood_group=="Brooklyn")

ggplot(AIRBnB, aes(x=longitude,y=latitude)) + 
  geom_point() + labs(x="Latitude", y="Longitude", title="Map of AirBnB Listings in Manhattan and Brooklyn")

AIRBnB_n <- AIRBnB %>% group_by(neighbourhood) %>%
  summarize(n=n())

AIRBnB <- merge(AIRBnB,AIRBnB_n) %>% filter(neighbourhood_group=="Manhattan"|n>=250)

ggplot(AIRBnB, aes(x=longitude,y=latitude)) + 
  geom_point() + labs(x="Latitude", y="Longitude", title="Map of AirBnB Listings in Manhattan and Brooklyn")

ggplot(AIRBnB, aes(x=longitude,y=latitude)) +
  geom_point(aes(color=price),position='jitter') +
  stat_density_2d(aes(fill= ..level..),geom="polygon") +
  geom_point(aes(x=-73.9855,y=40.7580),pch=24,color="red") +
  labs(x="Latitude", y="Longitude", title="Price Level Map of AirBnBs in Manhattan and North Brooklyn",caption="*Times Square Represented by Red Triangle on Map")

neighbourhoodaverages <- AIRBnB %>% group_by(neighbourhood) %>%
  summarize(price=mean(price),latitude=mean(latitude),longitude=mean(longitude))

summary(AIRBnB$neighbourhood)

ggplot(neighbourhoodaverages, aes(x=longitude, y=latitude, color=price)) + 
  geom_point() +
  labs(x="Latitude", y="Longitude", title="Average Price of AIRBnB Listings by Neighbourhood", caption="*Times Square Represented by Red Triangle on Map") +
  geom_point(aes(x=-73.9855,y=40.7580),pch=24,color="red") +
  geom_text(aes(label=neighbourhood), check_overlap = T)

ggplot(neighbourhoodaverages, aes(x=longitude, y=latitude, color=price)) + 
  geom_point() +
  labs(x="Latitude", y="Longitude", title="Average Price of AIRBnB Listings by Neighbourhood", caption="*Times Square Represented by Red Triangle on Map") +
  geom_point(aes(x=-73.9855,y=40.7580),pch=24,color="red")


# the following two plots were made with the help of the tutorial on NYC mapping at https://rpubs.com/jhofman/nycmaps.

lookup_code("New York", "New York")
nyc_tracts <- tracts(state = '36', county = c('061','047','081','005','085'))
r <- GET('http://data.beta.nyc//dataset/0ff93d2d-90ba-457c-9f7e-39e47bf2ac5f/resource/35dd04fb-81b3-479b-a074-a27a37888ce7/download/d085e2f8d0b54d4590b1e7d1f35594c1pediacitiesnycneighborhoods.geojson')
nyc_neighborhoods <- readOGR(content(r,'text'), 'OGRGeoJSON', verbose = F)
nyc_neighborhoods_df <- tidy(nyc_neighborhoods)

ggplot() + 
  geom_polygon(data=nyc_neighborhoods_df, aes(x=long, y=lat, group=group)) +
  geom_point(data=neighbourhoodaverages, aes(x=longitude, y=latitude, color=price)) +
  scale_color_gradient(low="blue", high="red") +
  labs(x="Latitude", y="Longitude", title="Average Price of AIRBnB Listings by Neighbourhood", caption="*Times Square Represented by White Triangle on Map") +
  geom_point(aes(x=-73.9855,y=40.7580),pch=24,color="white")


options(digits = 3)
set.seed(1234)
theme_set(theme_minimal())

m <- leaflet(neighbourhoodaverages) %>%
  addTiles() %>%
  addMarkers(lng = -73.9855, lat = 40.7580,
             popup = "Times Square") %>%
  addCircles(lng= ~longitude, lat= ~latitude, weight=1, radius=~sqrt(price)*30,
             popup = paste("Neighbourhood:", neighbourhoodaverages$neighbourhood, "<br>",
                           "Average Price:", neighbourhoodaverages$price, "<br>"))

m

mapshot(m,file = paste0(getwd(), "/map.png"))

p <- 0.017453292519943295;
AIRBnB$dlon <- abs(AIRBnB$longitude+73.9855)*p
AIRBnB$dlat <- abs(AIRBnB$latitude-40.7580)*p
AIRBnB$a <- (sin(AIRBnB$dlat/2) * sin(AIRBnB$dlat/2)) + cos(40.7580*p) * cos(AIRBnB$latitude*p) * (sin(AIRBnB$dlon/2) * sin(AIRBnB$dlon/2))
AIRBnB$c <- 2 * atan2(sqrt(AIRBnB$a),sqrt(1-AIRBnB$a))
AIRBnB$Distance <- 3961 * AIRBnB$c # Distance in miles

AIRBnB <- AIRBnB %>% filter(neighbourhood_group=="Manhattan")
AIRBnB$Distance.f <-factor(AIRBnB$Distance,levels=c("Very Close", "Close", "Somewhat Close", "Not Close or Far", "Far"))
AIRBnB$Distance.f[AIRBnB$Distance<=0.9]<-"Very Close"
AIRBnB$Distance.f[AIRBnB$Distance>0.9 & AIRBnB$Distance<= 1.5]<-"Close"
AIRBnB$Distance.f[AIRBnB$Distance>1.5 & AIRBnB$Distance<= 2.2]<-"Somewhat Close"
AIRBnB$Distance.f[AIRBnB$Distance>2.2 & AIRBnB$Distance<= 3]<-"Not Close or Far"
AIRBnB$Distance.f[AIRBnB$Distance>3 & AIRBnB$Distance<= 6]<-"Far"
table(AIRBnB$Distance.f)

averageprice <- AIRBnB %>%
  group_by(Distance.f) %>%
  summarise(avg=mean(price, na.rm =T)) %>%
  filter(Distance.f=="Very Close"|Distance.f=="Close"|Distance.f=="Somewhat Close"|Distance.f=="Not Close or Far"|Distance.f=="Far")
averageprice
ggplot(averageprice, aes(x= Distance.f, y=avg)) +
  geom_bar(color = "green", stat ='identity') +
  labs(x="Distance to Time Square", y= "Average Price", title="Average Price Compared to Proximity to Time Square", subtitle="Average Price of Entire Home/Apartment AirBnB in Manhattan")

AIRBnB <- read.csv("AIRBnB_NYC.csv")

# number of listings by area of NYC
# the most listings come from Manhattan and Brooklyn (and room types)
ggplot(AIRBnB, aes(neighbourhood_group)) + 
  geom_bar(aes(fill=room_type)) +
  labs(x="NYC Neighbourhood Groups", y="Number of Listings", title="Density of Listings for Each Area of NYC")

# Investigating the median price in Manhattan and Brooklyn
AIRBnB_MB <- AIRBnB %>%
  filter(neighbourhood_group=="Manhattan"|neighbourhood_group=="Brooklyn",price<500)
ggplot(AIRBnB_MB, aes(x=neighbourhood_group , y=price, fill=factor(room_type))) +
  geom_boxplot() +
  labs(x="Top Two Neighbourhood Groups", y="Price ($)", title="Median Price of Manhattan and Brooklyn")

# Investigating Manhattan's top 6 neighbourhoods (and room types)
AIRBnB_Manhattan <- AIRBnB %>% 
  filter(neighbourhood_group=="Manhattan",neighbourhood=="East Village"|
           neighbourhood=="Harlem"|neighbourhood=="Hell's Kitchen"|
           neighbourhood=="Midtown"|neighbourhood=="Upper East Side"|
           neighbourhood=="Upper West Side")
ggplot(AIRBnB_Manhattan, aes(neighbourhood)) +
  geom_bar(aes(fill=room_type)) + coord_flip() +
  labs(x="Number of Listings", y="Top Neighbourhoods in Manhattan", title="Six Most Listing-Dense Neighbourhoods in Manhattan")
AIRBnB_Manhattan <- AIRBnB_Manhattan %>% filter(price<500)
ggplot(AIRBnB_Manhattan, aes(x=neighbourhood,y=price,fill=factor(room_type))) +
  geom_boxplot() +
  labs(x="Neighbourhood", y="Price ($)", title="Median Price of Top Manhattan Neighbourhoods")

# Investigating Brooklyn's top 4 neighbourhoods (and room types)
AIRBnB_Brooklyn <- AIRBnB %>% 
  filter(neighbourhood_group=="Brooklyn",neighbourhood=="Williamsburg"|
           neighbourhood=="Crown Heights"|neighbourhood=="Bushwick"|
           neighbourhood=="Bedford-Stuyvesant")
ggplot(AIRBnB_Brooklyn, aes(neighbourhood)) + 
  geom_bar(aes(fill=room_type)) + coord_flip()+
  labs(x="Number of Listings", y="Top Neighbourhoods in Brooklyn", title="Four Most Listing-Dense Neighbourhoods in Brooklyn")
AIRBnB_Brooklyn <- AIRBnB_Brooklyn %>% filter(price<500)
ggplot(AIRBnB_Brooklyn, aes(x=neighbourhood,y=price,fill=factor(room_type))) +
  geom_boxplot() +
  labs(x="Neighbourhood", y="Price ($)", title="Median Price of Top Brooklyn Neighbourhoods")

AIRBnB2 <- read.csv("AIRBnB_NYC.csv")
singleMB <- AIRBnB2 %>%
  filter(room_type=="Entire home/apt", neighbourhood_group=="Manhattan"|neighbourhood_group=="Brooklyn")

AIRBnB_priceluxury1 <- AIRBnB2 %>% filter(price>350&price<=500)

ggplot(AIRBnB_priceluxury1, aes(price, na.rm = T)) + 
  geom_histogram(aes(y = ..density..),fill = "green", col= "red", alpha = 0.2)

AIRBnB_priceluxury2 <- AIRBnB2 %>% filter(price>500&price<=1000)

ggplot(AIRBnB_priceluxury2, aes(price, na.rm = T)) + 
  geom_histogram(aes(y = ..density..),fill = "green", col= "red", alpha = 0.2)

AIRBnB_priceluxury3 <- AIRBnB2 %>% filter(price>1000&price<=2000)

ggplot(AIRBnB_priceluxury3, aes(price, na.rm = T)) + 
  geom_histogram(aes(y = ..density..),fill = "green", col= "red", alpha = 0.2)

AIRBnB_priceluxury4 <- AIRBnB2 %>% filter(price>2000)

ggplot(AIRBnB_priceluxury4, aes(price, na.rm = T)) + 
  geom_histogram(aes(y = ..density..),fill = "green", col= "red", alpha = 0.2)

Airb <-singleMB %>% filter(price<350)
Outliers <-singleMB %>% filter(price>350)

ggplot(Airb, aes(x=neighbourhood_group, y=price)) + geom_boxplot()


#Trend
#Availability-Manhattan outliers have higher number of days when listing is available for booking, Brookyln is the same
ggplot(Outliers, aes(x=neighbourhood_group, y=availability_365)) +geom_boxplot()

ggplot(Airb, aes(neighbourhood_group, y = availability_365)) + geom_boxplot()

#Number of reviews- Outliers have a lot less reviews
ggplot(Outliers, aes(x=neighbourhood_group, y=number_of_reviews)) +geom_boxplot()

ggplot(Airb, aes(neighbourhood_group, y = number_of_reviews)) + geom_boxplot()

#minimum nights- No trend
ggplot(Outliers, aes(x=neighbourhood_group, y=minimum_nights)) +geom_boxplot()

ggplot(Airb, aes(neighbourhood_group, y = minimum_nights)) + geom_boxplot()

#reviews per month- outliers have less reviews per month
ggplot(Outliers, aes(x=neighbourhood_group, y=reviews_per_month)) +geom_boxplot()

ggplot(Airb, aes(neighbourhood_group, y = reviews_per_month)) + geom_boxplot()

#calculated list hostings- outliers hosts have less listings per host
ggplot(Outliers, aes(x=neighbourhood_group, y=calculated_host_listings_count)) +geom_boxplot()

ggplot(Airb, aes(neighbourhood_group, y = calculated_host_listings_count)) + geom_boxplot()