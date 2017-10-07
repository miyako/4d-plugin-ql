# 4d-plugin-ql
Use [QuickLook](https://developer.apple.com/documentation/quicklook) API to generate thumbnails and previews.

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|||

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />

---

## Syntax

```
thumbnail:=QL Create thumbnail (path;options)
```

Parameter|Type|Description
------------|------------|----
path|TEXT|
options|TEXT|JSON in/out
thumbnail|PICTURE|

Valid properties of ``options`` on input are ``scaleFactor``, ``width`` and ``height``.

```
preview:=QL Create preview (path;type;data;options)
```

Parameter|Type|Description
------------|------------|----
path|TEXT|
type|ARRAY TEXT|
data|ARRAY BLOB|
options|TEXT|JSON in/out
preview|BLOB|

Possible properties of options on output:

```
height
PDFStyle
baseBundlePath (converted to HFS)
textEncoding
pageElementXPath
mimeType
width
allowJavascript
```

No known generators seem to process ``options`` on input.
