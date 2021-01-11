![version](https://img.shields.io/badge/version-16%2B-8331AE)
![platform](https://img.shields.io/static/v1?label=platform&message=osx-64&color=blue)

# 4d-plugin-ql
Use [QuickLook](https://developer.apple.com/documentation/quicklook) API to generate thumbnails and previews.

### Remarks

to dump "c" symbols from ``qlmanage``

```
nm -g /usr/bin/qlmanage
```

to dump "obj-c" symbols from ``qlmanage``

```
otool -ov /usr/bin/qlmanage
```

or use [class-dump](https://github.com/nygard/class-dump)

previous version was using a hidden function ``QLPreviewCopyData`` to generate preview.

this API has been removed (at least, on Catalina).

current version is using ``- synchronousGetData`` of the hidden ``QLPreview`` class.

### Syntax

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

Possible properties of ``options`` on output:

```
height
PDFStyle (0=standard, 3=right, 4=left)
baseBundlePath (converted to HFS)
textEncoding
pageElementXPath
mimeType
width
allowJavascript
```

No known generators seem to process ``options`` on input.

For documents with multiple pages, an HTML preview is generally returned.

If the preview document is a single page, the data is returned in ``preview``. You can use ``mimeType`` to find out its internal format. The generator decides what kind of preview to draw. For example, Microsoft Office generators tend to create JPG. Apple iWorks tend to create PDF.

If the preview document has several pages, the data is returned in ``data`` and a container HTML is returned in ``preview``. The ``cid`` of each page is returned in  ``type``. 

Note that QuickLook is actually a **collection of generators and viewers**. A "preview" is not limited to image, it can be audio, video, etc. Likewise, the viewer could be a web browser engine, PDF or text viewer, even a media player or stream player (``baseBundlePath`` indicates the type of viewer). 
