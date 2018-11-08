# Project Proposal
## Personal Youtube Data Visualizer
My project will analyze the usage statistics of a user's Youtube account. The key statistics I want to visualize are 
**Most watched video of all time**
**Rank subscriptions based on most watched**
**Most common category of video watched (?)**
**Time spent in days, hours, minutes, and seconds**
**Trend of time spent on Youtube**


***Application Breakdown***
1. Getting the data
    * Theoretically, I will get the data through the [Youtube Reporting API](https://developers.google.com/youtube/reporting/). 
    * Naturally, a user will have to log in to his/her account so I will implement OAuth and create a log-in page for my application. I plan to use this link to [implement OAuth](https://developers.google.com/youtube/v3/guides/authentication#OAuth2_Devices_Flow)
2. Analysis
    * Then I will use my own statistical methods to find propertiess, such as the mean (for usage in time watched per day). 
3. The Visualization
    * The graphs and various visualizations will be handled by a framework called [ofxGraphica](https://github.com/jagracar/ofxGrafica)
4. The GUI
    * I would rather sacrifice functionality in my program for cleanliness in my GUI so I will spend a significant amount of time in styling the GUI. Most likely, I will use a Red and White color scheme to match Youtube's. 

***Timeline of the Project***
