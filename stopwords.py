
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
import pandas as pd
import numpy as np

def readData():
    data = pd.read_csv('rows.csv')
    data = data.drop(['Date received','Sub-product','Sub-issue','Consumer complaint narrative', 'Company public response', 'Tags', 'Consumer consent provided?', 'Submitted via','Date sent to company', 'Company response to consumer','Timely response?', 'Consumer disputed?'], axis=1)
    data['Issue'] = data['Issue'].str.replace(r'[^\w\s]+', '')
    data['Product'] = data['Product'].str.replace(r'[^\w\s]+', '')
    data['Company'] = data['Company'].str.replace(r'[^\w\s]+', '')
    data = data.dropna()
    data.to_csv('newdata.csv')
    # return data

# still under development
def removeStopWords():
    stop_words = set(stopwords.words('english'))
    data = pd.read_csv('newdata.csv')

    filtered_sentence = []
    c = 0
    for index, row in data.iterrows():
        # if c == 20:
        #     break
        # c+=1
        sentence = row['Issue']
        word_tokens = word_tokenize(sentence)
        for w in word_tokens:
            if w not in stop_words:
                filtered_sentence.append(w)
        listToStr = ' '.join([str(elem) for elem in filtered_sentence])
        # print(word_tokens)
        # print(listToStr)
        # print(index, listToStr)
        # data.loc[index,'Issue'] = listToStr
        data.loc[index, 'Issue'] = listToStr
        # print(data.at[index, 'Issue'])

        filtered_sentence = []
    data.to_csv('nostopwords.csv', index = False)

# removeStopWords()
if __name__ == '__main__':
    # readData()
    removeStopWords()



# print(stopwords.words('english'))