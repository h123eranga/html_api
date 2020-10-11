# TAG:div:TAG:span:INNER_TEXT:test:END:span:END:div:

tokens = "TAG:div:TAG:span:INNER_TEXT:test:END:span:END:div:"

print(tokens)

class DomElement:
    def __init__(self,tag,innerText,childElements):
        self.tag=tag
        self.innerText=innerText
        self.childElements=childElements

domElement = DomElement("div","test",None)

def getDomTree(domElement):
    for i in range(len(tokens)):
        if(tag): # div
            dom=  getDomTree(None)
             dom.tag = tag
        if(innerText):
            domElement.innerText = innerText
        if(tag):
            domElement.tag = tag
    return domElement