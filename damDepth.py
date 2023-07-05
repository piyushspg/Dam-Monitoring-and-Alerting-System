import pandas as pd
import numpy as np
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

data = pd.read_csv('/content/mydata.csv')

X = data[['upstream_level', 'downstream_level']]
y = data['dam_open']
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=123)

dt = DecisionTreeClassifier(max_depth=2,random_state=123)
dt.fit(X_train, y_train)

y_pred = dt.predict(X_test)

plt.figure(figsize=(12,8))
plot_tree(dt, filled=True, feature_names=['upstream_level', 'downstream_level'], class_names=['closed', 'open'])
plt.show()
print(f"Classification Report: \n{classification_report(y_test, y_pred)}")
print(f"Confusion Matrix: \n{confusion_matrix(y_test, y_pred)}")
