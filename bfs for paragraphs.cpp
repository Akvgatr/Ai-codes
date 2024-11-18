#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <string>

using namespace std;

class Graph {
    int n; // Number of nodes in the graph
public:
    vector<vector<int> > mat; // Adjacency matrix

    Graph() {
        n = 28; // 26 letters + '.' + ' '
        mat.resize(n);
        for (int i = 0; i < n; ++i) {
            mat[i].resize(n, 0);
        }
    }

    int get_index(char ch) {
        if (ch == '.') return 26;
        else if (ch == ' ') return 27;
        else return ch - 'a';
    }

    char get_char(int i) {
        if (0 <= i && i <= 25) return 'a' + i;
        else if (i == 26) return '.';
        else return ' ';
    }

    void createGraph(string s) {
        int str_len = s.length();
        int prev_idx = get_index(s[0]);
        for (int i = 1; i < str_len; i++) {
            char ch = s[i];
            int curr_idx = get_index(ch);
            mat[prev_idx][curr_idx]++;
            prev_idx = curr_idx;
        }
    }

    void display_matrix() {
        int width = 5;
        cout << "Adjacency Matrix : \n\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(width) << mat[i][j];
            }
            cout << endl;
        }
        cout << "\n\n";
    }
};

string refine_input(string input) {
    string s = "";
    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        if (ch == '.' || ch == ' ' || ('a' <= ch && ch <= 'z')) {
            s += ch; // Append valid characters
        } else if ('A' <= ch && ch <= 'Z') {
            ch = tolower(ch); // Convert to lowercase
            s += ch; // Append converted character
        }
    }
    return s;
}

string best_first_search(Graph &g1) {
    int n = g1.mat.size();
    queue<int> q;
    vector<int> vis(n, 0);
    string output = "";
    char start_char;
    
    cout << "Enter the starting character: ";
    cin >> start_char;
    
    if (!(start_char == ' ' || start_char == '.' || ('a' <= start_char && start_char <= 'z'))) {
        cout << "INVALID STARTING CHARACTER.\n";
        return output;
    }
    
    int start_index = g1.get_index(start_char);
    q.push(start_index);
    vis[start_index] = 1;

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        char ch = g1.get_char(vertex);
        output += ch; // Append current character to output

        int maxi_freq = -1e9;
        int at_index = -1;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && g1.mat[vertex][i] != 0) {
                if (maxi_freq < g1.mat[vertex][i]) {
                    maxi_freq = g1.mat[vertex][i];
                    at_index = i;
                }
            }
        }
        if (at_index != -1) {
            q.push(at_index);
            vis[at_index] = 1; // Mark this index as visited
        }
    }
    return output;
}

int main() {
    string input;
    cout << "Enter the input string: ";
    getline(cin, input); // Read entire line including spaces

    Graph g;
    string refined_input_str = refine_input(input);
    g.createGraph(refined_input_str);
    g.display_matrix();

    string output = best_first_search(g);
    cout << "Best-first search result: " << output << endl;

    return 0;
}



//Everything was in confusion in the Oblonskys' house. The wife had discovered that the husband was carrying on an intrigue with a French girl, who had been a governess in their family, and she had announced to her husband that she could not go on living in the same house with him. This position of affairs had now lasted three days, and not only the husband and wife themselves, but all the members of their family and household, were painfully conscious of it. Every person in the house felt that there was no sense in their living together, and that the stray people brought together by chance in any inn had more in common with one another than they, the members of the family and household of the Oblonskys. The wife did not leave her own room, the husband had not been at home for three days. The children ran wild all over the house; the English governess quarreled with the housekeeper, and wrote to a friend asking her to look out for a new situation for her; the man-cook had walked off the day before just at dinner time; the kitchen-maid, and the coachman had given warning. Three days after the quarrel, Prince Stepan Arkadyevitch Oblonsky--Stiva, as he was called in the fashionable world woke up at his usual hour, that is, at eight o'clock in the morning, not in his wife's bedroom, but on the leather-covered sofa in his study. He turned over his stout, well-cared-for person on the springy sofa, as though he would sink into a long sleep again; he vigorously embraced the pillow on the other side and buried his face in it; but all at once he jumped up, sat up on the sofa, and opened his eyes. Stepan Arkadyevitch's eyes twinkled gaily, and he pondered with a smile. There was a great deal more that was delightful, only there's no putting it into words, or even expressing it in one's thoughts awake." And noticing a gleam of light peeping in beside one of the serge curtains, he cheerfully dropped his feet over the edge of the sofa, and felt about with them for his slippers, a present on his last birthday, worked for him by his wife on gold-colored morocco. And, as he had done every day for the last nine years, he stretched out his hand, without getting up, towards the place where his dressing-gown always hung in his bedroom. And thereupon he suddenly remembered that he was not sleeping in his wife's room, but in his study, and why: the smile vanished from his face, he knitted his brows. Most unpleasant of all was the first minute when, on coming, happy and goodhumored, from the theater, with a huge pear in his hand for his wife, he had not found his wife in the drawing-room, to his surprise had not found her in the study either, and saw her at last in her bedroom with the unlucky letter that revealed everything in her hand. She, his Dolly, forever fussing and worrying over household details, and limited in her ideas, as he considered, was sitting perfectly still with the letter in her hand, looking at him with an expression of horror, despair, and indignation. And at this recollection, Stepan Arkadyevitch, as is so often the case, was not so much annoyed at the fact itself as at the way in which he had met his wife's words. There happened to him at that instant what does happen to people when they are unexpectedly caught in something very disgraceful. He did not succeed in adapting his face to the position in which he was placed towards his wife by the discovery of his fault. Instead of being hurt, denying, defending himself, begging forgiveness, instead of remaining indifferent even--anything would have been better than what he did do--his face utterly involuntarily (reflex spinal action, reflected Stepan Arkadyevitch, who was fond of physiology)--utterly involuntarily assumed its habitual, good-humored, and therefore idiotic smile. This idiotic smile he could not forgive himself. Catching sight of that smile, Dolly shuddered as though at physical pain, broke out with her characteristic heat into a flood of cruel words, and rushed out of the room. Since then she had refused to see her husband.
