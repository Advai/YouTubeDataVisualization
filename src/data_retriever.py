# Sample Python code for user authorization

import os
import sys
import google.oauth2.credentials
import google_auth_oauthlib.flow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError
from google_auth_oauthlib.flow import InstalledAppFlow
import json

# The CLIENT_SECRETS_FILE variable specifies the name of a file that contains
# the OAuth 2.0 information for this application, including its client_id and
# client_secret.
CLIENT_SECRETS_FILE = "C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\client_secret.json"

# This OAuth 2.0 access scope allows for full read/write access to the
# authenticated user's account and requires requests to use an SSL connection.
SCOPES = ['https://www.googleapis.com/auth/youtube.force-ssl']
API_SERVICE_NAME = 'youtube'
API_VERSION = 'v3'
topicIds = {
"/m/04rlf":"Music (parent topic)",
"/m/02mscn": "Christian music",
"/m/0ggq0m": "Classical music",
"/m/01lyv": "Country",
"/m/02lkt": "Electronic music",
"/m/0glt670": "Hip hop music",
"/m/05rwpb": "Independent music",
"/m/03_d0": "Jazz",
"/m/028sqc": "Music of Asia",
"/m/0g293": "Music of Latin America",
"/m/064t9": "Pop music",
"/m/06cqb": "Reggae",
"/m/06j6l": "Rhythm and blues",
"/m/06by7": "Rock music",
"/m/0gywn": "Soul music",
"/m/0bzvm2": "Gaming (parent topic)",
"/m/025zzc": "Action game",
"/m/02ntfj": "Action-adventure game",
"/m/0b1vjn": "Casual game",
"/m/02hygl": "Music video game",
"/m/04q1x3q": "Puzzle video game",
"/m/01sjng": "Racing video game",
"/m/0403l3g": "Role-playing video game",
"/m/021bp2": "Simulation video game",
"/m/022dc6": "Sports game",
"/m/03hf_rm": "Strategy video game",
"/m/06ntj": "Sports (parent topic)",
"/m/0jm_": "American football",
"/m/018jz": "Baseball",
"/m/018w8": "Basketball",
"/m/01cgz": "Boxing",
"/m/09xp_": "Cricket",
"/m/02vx4": "Football",
"/m/037hz": "Golf",
"/m/03tmr": "Ice hockey",
"/m/01h7lh": "Mixed martial arts",
"/m/0410tth": "Motorsport",
"/m/07bs0": "Tennis",
"/m/07_53": "Volleyball",
"/m/02jjt": "Entertainment (parent topic)",
"/m/09kqc": "Humor",
"/m/02vxn": "Movies",
"/m/05qjc": "Performing arts",
"/m/066wd": "Professional wrestling",
"/m/0f2f9": "TV shows",
"/m/019_rr": "Lifestyle (parent topic)",
"/m/032tl": "Fashion",
"/m/027x7n": "Fitness",
"/m/02wbm": "Food",
"/m/03glg": "Hobby",
"/m/068hy": "Pets",
"/m/041xxh": "Physical attractiveness [Beauty]",
"/m/07c1v": "Technology",
"/m/07bxq": "Tourism",
"/m/07yv9": "Vehicles",
"/m/098wr": "Society (parent topic)",
"/m/09s1f": "Business",
"/m/0kt51": "Health",
"/m/01h6rj": "Military",
"/m/05qt0": "Politics",
"/m/06bvp": "Religion",
"/m/01k8wb": "Knowledge",
}

def get_authenticated_service():
    flow = InstalledAppFlow.from_client_secrets_file(CLIENT_SECRETS_FILE, SCOPES)
    credentials = flow.run_console()
    return build(API_SERVICE_NAME, API_VERSION, credentials=credentials)


def channels_list_by_username(service, **kwargs):
    results = service.subscriptions().list(
        **kwargs
    ).execute()

    print('This channel\'s ID is %s. Its title is %s' %
          (results['items'][0]['id'],
           results['items'][0]['snippet']['title']))
    # results['items'][0]['statistics']['viewCount'])
    response = service.subscriptions().list(part='snippet,contentDetails', mine=True).execute()
    topicids = service.channels().list(part="snippet, contentDetails, topicDetails",
                                       id=results['items'][0]['snippet']['resourceId']['channelId']).execute()
    print(topicids)
    print(response)


def liked_videos_data(service):
    results = service.videos().list(
        part='snippet,contentDetails,statistics',
        myRating='like',
        maxResults=50
    ).execute()
    videoCategories = service.videoCategories().list(
        part='snippet',
        regionCode='US'
    ).execute()
    category_dict = dict()
    final_category_dict = dict()
    final_category_dict['items'] = list()
    for i in range(len(videoCategories['items'])):
        tempDict = dict()
        tempDict[videoCategories['items'][i]['id']] = videoCategories['items'][i]['snippet']['title']
        category_dict[videoCategories['items'][i]['id']] = videoCategories['items'][i]['snippet']['title']
        final_category_dict['items'].append(videoCategories['items'][i]['snippet']['title'])
    with open("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\video_categories.json", 'w') as outfile:
        json.dump(final_category_dict, outfile, indent=3)
    final_video_data_json = dict()
    final_video_data_json['items'] = list()
    for i in range(len(results['items'])):
        video_data_dict = dict()
        if len(results['items'][i]['snippet']['title'].split(' ')) > 7:
            temp = results['items'][i]['snippet']['title'].split(' ', 7)
            temp.pop()
            results['items'][i]['snippet']['title'] = " ".join(temp)
        video_data_dict['title'] = results['items'][i]['snippet']['title']
        video_data_dict['viewCount'] = float(results['items'][i]['statistics']['viewCount'])
        video_data_dict['likeCount'] = float(results['items'][i]['statistics']['likeCount'])
        video_data_dict['category'] = category_dict[results['items'][i]['snippet']['categoryId']]
        final_video_data_json['items'].append(video_data_dict)
    with open("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\liked_video_data.json", 'w') as outfile:
        json.dump(final_video_data_json, outfile, indent=3)


def subscribtions_data_by_channel(service):
    results = service.subscriptions().list(
        part='snippet,contentDetails',
        mine=True,
        maxResults=50
    ).execute()
    final_topic_json = dict()
    final_topic_json['items'] = list()
    for key in topicIds:
        final_topic_json['items'].append(topicIds[key])
    with open("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\topic_ids.json", 'w') as outfile:
        json.dump(final_topic_json, outfile, indent=3)
    channel_data_list = list()
    channelIdList = list()
    final_channel_json_obj = dict()
    final_channel_json_obj['items'] = list()
    for i in range(len(results['items'])):
        # print(results['items'][i]['snippet']['resourceId']['channelId'])
        channelIdList.append(results['items'][i]['snippet']['resourceId']['channelId'])
        channel_response = service.channels().list(
            part='snippet,contentDetails,statistics,topicDetails',
            id=results['items'][i]['snippet']['resourceId']['channelId']
        ).execute()
        channel_json_obj = dict()
        channel_json_obj['title'] = channel_response['items'][0]['snippet']['title']
        channel_json_obj['viewCount'] = float(channel_response['items'][0]['statistics']['viewCount'])
        channel_json_obj['subscriberCount'] = float(channel_response['items'][0]['statistics']['subscriberCount'])
        topicStrs = []
        topicSet = set()
        for i in range(len(channel_response['items'][0]['topicDetails']['topicIds'])):
            if (topicIds[channel_response['items'][0]['topicDetails']['topicIds'][i]] not in topicSet):
                topicStrs.append(topicIds[channel_response['items'][0]['topicDetails']['topicIds'][i]])
                topicSet.add(topicIds[channel_response['items'][0]['topicDetails']['topicIds'][i]])
            # topicStrs.append(topicIds[channel_response['items'][0]['topicDetails']['topicIds'][i]])
        channel_json_obj['topicIds'] = topicStrs  # channel_response['items'][0]['topicDetails']['topicIds']
        # print(channel_json_obj['title'])
        final_channel_json_obj['items'].append(channel_json_obj)
        # print(channel_json_obj)
    with open("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\subscription_data.json", 'w') as outfile:
        json.dump(final_channel_json_obj, outfile, indent=3)


if __name__ == '__main__':
    # When running locally, disable OAuthlib's HTTPs verification. When
    # running in production *do not* leave this option enabled.
    os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'
    service = get_authenticated_service()
    # channels_list_by_username(service,
    #                           part='snippet,contentDetails',
    #                           mine=True)
    subscribtions_data_by_channel(service)
    liked_videos_data(service)
    print("Data Retrieved")