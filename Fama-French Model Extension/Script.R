library(car)

# Load dataset
data <- read.csv('regression_data.csv')

# Calculating excess retruns
data$WMT_ExR = data$WMT_R - data$RF

set.seed(110)

# Split into training and testing set
subset <- sample(c(TRUE, FALSE), nrow(data), replace=TRUE, prob=c(0.75, 0.25))

train <- data[subset, ]
test <- data[!subset, ]

# Run regression
regression_model_2 <- lm(WMT_ExR ~ MRP + SMB + HML + INF, data = train)

summary(regression_model_2)

# Checking assumptions
plot(regression_model_2$fitted.values, regression_model_2$residuals)
abline(h=0)
qqnorm(regression_model_2$residuals)
hist(regression_model_2$residuals)

# Multicollinearity check
cor_matrix <- cor(train[, c("MRP", "SMB", "HML", "INF")])
cor_matrix

# Std. dev. of excess returns
sd(train$WMT_ExR)

# RMSE calculation
sqrt(mean((test$WMT_ExR - predict(regression_model_2, test))^2))

# Using model to make prediction
newdata <- data.frame(MRP = c(4.3), SMB = c(-2.4), HML = c(1.2), INF = c(0.7))

predict(regression_model_2, newdata = newdata, interval = "confidence")






