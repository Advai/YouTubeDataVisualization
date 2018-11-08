# Project Proposal
## Personal Youtube Data Visualizer
My project will analyze the usage statistics of a user's Youtube account. The key statistics I want to visualize are: <br/>
**Most watched video of all time**<br/>
**Rank subscriptions based on most watched**<br/>
**Most common category of video watched (?)**<br/>
**Time spent in days, hours, minutes, and seconds**<br/>
**Trend of time spent on Youtube**<br/>


### Application Breakdown
1. Getting the data
    * Theoretically, I will get the data through the [Youtube Reporting API](https://developers.google.com/youtube/reporting/). 
    * Naturally, a user will have to log in to his/her account so I will implement OAuth and create a log-in page for my application. I plan to use this link to [implement OAuth](https://developers.google.com/youtube/v3/guides/authentication#OAuth2_Devices_Flow)
2. Analysis
    * Then I will use my own statistical methods to find propertiess, such as the mean (for usage in time watched per day). 
3. The Visualization
    * The graphs and various visualizations will be handled by a framework called [ofxGraphica](https://github.com/jagracar/ofxGrafica)
4. The GUI
    * I would rather sacrifice functionality in my program for cleanliness in my GUI so I will spend a significant amount of time in styling the GUI. Most likely, I will use a Red and White color scheme to match Youtube's. 

### Timeline of the Project
   1. 11/8-11/15
      1. Read more about Youtube Analytics
      2. Make mockup of GUI Design
      3. Finish the timeline
   2. 11/15 - 11/22
      
      
### Some useful links <br/>
[Guide to Youtube Analytics](https://www.singlegrain.com/blog-posts/analytics/complete-guide-to-youtube-analytics/)<br/>
[Didn't have time to parse every link here but there might be something useful](https://github.com/uhub/awesome-cpp) <br/>
[Data Model of Youtube Data](https://developers.google.com/youtube/analytics/data_model)  <br/>
[Link to most common problems with Youtube API](https://stackoverflow.com/questions/tagged/youtube-analytics-api?sort=votes&pageSize=50) <br/>
