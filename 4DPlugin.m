/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : QL
 #	author : miyako
 #	2017/10/07
 #
 # --------------------------------------------------------------------------------*/

#include "4DPluginAPI.h"
#include "4DPlugin.h"

void PluginMain(PA_long32 selector, PA_PluginParameters params)
{
	PA_long32 pProcNum = selector;
	sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
	PackagePtr pParams = (PackagePtr)params->fParameters;
	
	CommandDispatcher(pProcNum, pResult, pParams);
}

void CommandDispatcher (PA_long32 pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
// --- QL

		case 1 :
			QL_Create_thumbnail(pResult, pParams);
			break;

		case 2 :
			QL_Create_preview(pResult, pParams);
			break;

	}
}

#pragma mark -

CFURLRef copyPathURL(PA_Unistring *str)
{
	if(str)
	{
		CFStringRef path = CFStringCreateWithCharacters(kCFAllocatorDefault, (const UniChar *)str->fString, (CFIndex)str->fLength);
		if(path)
		{
			return CFURLCreateWithFileSystemPath(kCFAllocatorDefault, path, kCFURLHFSPathStyle, false);
		}
	}
	
	return nil;
}

CFStringRef createFromWideChar(json_char *wstr)
{
	if(wstr)
	{
		size_t len = wcslen(wstr) * sizeof(wchar_t);
		uint32_t dataSize = (uint32_t)(len+sizeof(PA_Unichar));
		void *buf = malloc(dataSize);
		if(buf)
		{
			memset(buf, 0, dataSize);
			len = PA_ConvertCharsetToCharset((char *)wstr,
																			 (PA_long32)len,
																			 eVTC_UTF_32,
																			 (char *)buf,
																			 dataSize,
																			 eVTC_UTF_16);
			//return value of PA_ConvertCharsetToCharset() is bytes, not characters
			//extra length creates 0x0 invalidating isEqualToString
			return CFStringCreateWithCharacters(kCFAllocatorDefault, (const UniChar *)buf, len/sizeof(UniChar));
		}
	}
	
	return nil;
}

CFDictionaryRef copyOptions(PA_Unistring *str)
{
	CFMutableDictionaryRef options = CFDictionaryCreateMutable(kCFAllocatorDefault,
																														 0,
																														 &kCFTypeDictionaryKeyCallBacks,
																														 &kCFTypeDictionaryValueCallBacks);
	if(options)
	{
		if(str)
		{
			uint32_t dataSize = (uint32_t)((str->fLength * sizeof(wchar_t))+sizeof(wchar_t));
			void *buf = malloc(dataSize);
			if(buf)
			{
				memset(buf, 0, dataSize);
				PA_ConvertCharsetToCharset((char *)str->fString,
																	 str->fLength * sizeof(PA_Unichar),
																	 eVTC_UTF_16,
																	 (char *)buf,
																	 dataSize,
																	 eVTC_UTF_32);
				JSONNODE *n = json_parse((const wchar_t *)buf);
				if(n)
				{
					for(json_index_t i = 0; i < json_size(n); ++i)
					{
						JSONNODE *c = json_at(n, i);
						/*
						 wprintf(L"json_name:%ls\n", json_name(c));
						 wprintf(L"json_as_string:%s\n", json_as_string(c));
						 */
						CFStringRef name = createFromWideChar(json_name(c));
						if(name)
						{
							if([(NSString *)name isEqualToString:@"scaleFactor"])
							{
								double doubleValue = json_as_float(c);
								CFNumberRef scaleFactor = CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &doubleValue);
								if(scaleFactor)
								{
									CFDictionarySetValue(options, name, scaleFactor);
									CFRelease(scaleFactor);
								}
							}else if([(NSString *)name isEqualToString:@"width"])
							{
								double doubleValue = json_as_float(c);
								CFNumberRef scaleFactor = CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &doubleValue);
								if(scaleFactor)
								{
									CFDictionarySetValue(options, name, scaleFactor);
									CFRelease(scaleFactor);
								}
							}else if([(NSString *)name isEqualToString:@"height"])
							{
								double doubleValue = json_as_float(c);
								CFNumberRef scaleFactor = CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &doubleValue);
								if(scaleFactor)
								{
									CFDictionarySetValue(options, name, scaleFactor);
									CFRelease(scaleFactor);
								}
							}else
							{
								CFStringRef value = createFromWideChar(json_as_string(c));
								if(value)
								{
									CFDictionarySetValue(options, name, value);
									CFRelease(value);
								}
							}
							CFRelease(name);
						}
					}
					json_delete(n);
				}
				free(buf);
			}
		}
	}
	
	return options;
}

void setOptions(PA_Unistring *str, CFDictionaryRef options)
{
	if(str)
	{
		NSError *error;
		NSData *data = [NSJSONSerialization dataWithJSONObject:(NSDictionary *)options
																									 options:0
																										 error:&error];
		if(data)
		{
			CFStringRef json = (CFStringRef)[[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
			if(json)
			{
				uint32_t dataSize = (uint32_t)((CFStringGetLength(json) * sizeof(UniChar))+sizeof(UniChar));
				void *buf = malloc(dataSize);
				if(buf)
				{
					memset(buf, 0, dataSize);
					CFStringGetCharacters(json, CFRangeMake(0, CFStringGetLength(json)), (UniChar *)buf);
					PA_SetUnistring(
													(PA_Unistring *)str,
													(PA_Unichar *)buf
													);
					free(buf);
				}
				CFRelease(json);
			}
		}
	}
}

#pragma mark common

#pragma mark QL

// -------------------------------------- QL --------------------------------------


void QL_Create_thumbnail(sLONG_PTR *pResult, PackagePtr pParams)
{
	CFURLRef url = copyPathURL((PA_Unistring *)pParams[0]);
	
	if(url)
	{
		CFDictionaryRef options = copyOptions((PA_Unistring *)pParams[1]);
		if(options)
		{			
			CGSize maxSize = CGSizeMake(1024, 1024);
			CFNumberRef doubleValue;
			if(CFDictionaryGetValueIfPresent(options, CFSTR("width"), (const void **)&doubleValue))
			{
				CGFloat w;
				if(CFNumberGetValue(doubleValue, kCFNumberDoubleType, &w))
				{
					maxSize.width = w;
				}			}
			if(CFDictionaryGetValueIfPresent(options, CFSTR("height"), (const void **)&doubleValue))
			{
				CGFloat h;
				if(CFNumberGetValue(doubleValue, kCFNumberDoubleType, &h))
				{
					maxSize.height = h;
				}
			}

			CGImageRef image = QLThumbnailImageCreate(kCFAllocatorDefault, url, maxSize, options);
			
			if(image)
			{
				CFMutableDataRef data = CFDataCreateMutable(kCFAllocatorDefault, 0);
				CGImageDestinationRef destination = CGImageDestinationCreateWithData(data, kUTTypeTIFF, 1, NULL);
				CFMutableDictionaryRef properties = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);
				
				CGImageDestinationAddImage(destination, image, properties);
				CGImageDestinationFinalize(destination);

				//$0<-
				PA_Picture picture = PA_CreatePicture((void *)CFDataGetBytePtr(data), (PA_long32)CFDataGetLength(data));
				*(PA_Picture*) pResult = picture;

				CFRelease(properties);
				CFRelease(destination);
				CFRelease(data);
	
				CGImageRelease(image);
			}else
			{
				NSString *path = (NSString *)CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
				if(path)
				{
					NSImage *image = [[NSWorkspace sharedWorkspace]iconForFile:path];
					//will be 1024x1024
					[image setSize:NSMakeSize(maxSize.width, maxSize.height)];
					NSData *data = [image TIFFRepresentation];
					//$0<-
					PA_Picture picture = PA_CreatePicture((void *)[data bytes], (PA_long32)[data length]);
					*(PA_Picture*) pResult = picture;
					[path release];
				}
		
			}
			
			CFRelease(options);
		}
		CFRelease(url);
	}
}

void QL_Create_preview(sLONG_PTR *pResult, PackagePtr pParams)
{
	PA_Variable param2 = (*(PA_Variable *)pParams[1]);
	PA_ResizeArray(&param2, 0);
	PA_SetArrayCurrent(&param2, 0);
	
	PA_Variable param3 = (*(PA_Variable *)pParams[2]);
	PA_ResizeArray(&param3, 0);
	PA_SetArrayCurrent(&param3, 0);
	
	CFMutableDictionaryRef returnOptions = CFDictionaryCreateMutable(kCFAllocatorDefault, 0,
																																	 &kCFTypeDictionaryKeyCallBacks,
																																	 &kCFTypeDictionaryValueCallBacks);
	if(returnOptions)
	{
		CFURLRef url = copyPathURL((PA_Unistring *)pParams[0]);
		
		if(url)
		{
			CFDictionaryRef options = copyOptions((PA_Unistring *)pParams[3]);
			if(options)
			{
				QLPreviewRef preview = QLPreviewCreate(kCFAllocatorDefault, url, options);
				if(preview)
				{
					CFDataRef data = QLPreviewCopyData(preview);//this is where the preview is actually created
					if(data)
					{
						//properties
						CFDictionaryRef properties = QLPreviewCopyProperties(preview);
						[(NSDictionary *)properties enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop)
						 {
							 if([(NSString *)key isEqualToString:@"Height"])
							 {
								 CFDictionarySetValue(returnOptions, CFSTR("height"), obj); return;
							 }else if([(NSString *)key isEqualToString:@"PDFStyle"])
							 {
								 CFDictionarySetValue(returnOptions, CFSTR("PDFStyle"), obj); return;
							 }else if([(NSString *)key isEqualToString:@"BaseBundlePath"])
							 {
								 //convert to hfs
								 CFURLRef u = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, (CFStringRef)obj, kCFURLPOSIXPathStyle, false);
								 if(u)
								 {
									 CFStringRef s = CFURLCopyFileSystemPath((CFURLRef)u, kCFURLHFSPathStyle);
									 if(s)
									 {
										 CFDictionarySetValue(returnOptions, CFSTR("baseBundlePath"), s);
										 CFRelease(s);
									 }
									 CFRelease(u);
								 }
								  return;
							 }else if([(NSString *)key isEqualToString:@"TextEncoding"])
							 {
								 CFDictionarySetValue(returnOptions, CFSTR("textEncoding"), obj); return;
							 }else if([(NSString *)key isEqualToString:@"PageElementXPath"])
							 {
								 CFDictionarySetValue(returnOptions, CFSTR("pageElementXPath"), obj); return;
							 }else if([(NSString *)key isEqualToString:@"MimeType"])
							 {
								 CFDictionarySetValue(returnOptions, CFSTR("mimeType"), obj); return;
							 }else if([(NSString *)key isEqualToString:@"Width"])
							 {
								 CFDictionarySetValue(returnOptions, CFSTR("width"), obj); return;
							 }else if([(NSString *)key isEqualToString:@"AllowJavascript"])
							 {
								 CFDictionarySetValue(returnOptions, CFSTR("allowJavascript"), obj); return;
							 }
	 
						 }];
						
						//properties.attachments
						if(CFDictionaryContainsKey(properties, kQLPreviewPropertyAttachmentsKey))
						{
							CFDictionaryRef attachments = CFDictionaryGetValue(properties, kQLPreviewPropertyAttachmentsKey);
							NSUInteger count = [(NSDictionary *)attachments count];
							PA_ResizeArray(&param2, (PA_long32)count);
							PA_ResizeArray(&param3, (PA_long32)count);
							__block NSUInteger nb = 1;
							[(NSDictionary *)attachments enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop)
							 {
								 //->$2
								 CFStringRef cid = (CFStringRef)key;
								 uint32_t dataSize = (uint32_t)((CFStringGetLength(cid) * sizeof(UniChar))+sizeof(UniChar));
								 void *buf = malloc(dataSize);
								 if(buf)
								 {
									 memset(buf, 0, dataSize);
									 CFStringGetCharacters(cid, CFRangeMake(0, CFStringGetLength(cid)), (UniChar *)buf);
									 PA_Unistring str = PA_CreateUnistring((PA_Unichar *)buf);
									 PA_SetStringInArray(param2, (PA_long32)nb, &str);
									 free(buf);
								 }
								 //->$3
								 CFDictionaryRef attachment = (CFDictionaryRef)obj;
								 NSData *data = (NSData *)CFDictionaryGetValue(attachment, kQLPreviewPropertyAttachmentDataKey);
								 PA_Variable element = PA_CreateVariable(eVK_Blob);
								 PA_SetBlobVariable(&element, (void *)[data bytes], (PA_long32)[data length]);
								 PA_SetBlobInArray(param3, (PA_long32)nb, element.uValue.fBlob);
								 
								 nb++;
 
							 }];
						}
						CFRelease(properties);
						
						//$0<-
						PA_Handle *h = (PA_Handle *)pResult;
						PA_Handle d = PA_NewHandle((PA_long32)CFDataGetLength(data));
						PA_MoveBlock((char *)CFDataGetBytePtr(data), PA_LockHandle(d), (PA_long32)CFDataGetLength(data));
						PA_UnlockHandle(d);
						*h = d;
		
						CFRelease(data);
					}//data

					//->$4
					CFDictionarySetValue(returnOptions, CFSTR("displayBundleID"), QLPreviewGetDisplayBundleID(preview));
					CFStringRef previewContentType = QLPreviewCopyPreviewContentType(preview);
					CFDictionarySetValue(returnOptions, CFSTR("previewContentType"), previewContentType);
					CFRelease(previewContentType);
					
					//can't convert array/dict to serialised json...
					/*
					 CFArrayRef inlinePreviewSupportedContentTypes = QLPreviewGetInlinePreviewSupportedContentTypes(preview);
					 CGSize sizeHint = QLPreviewGetPreviewSizeHint(preview);
					 */

					QLPreviewClose(preview);
				}//preview
				CFRelease(options);
			}//options
			CFRelease(url);
		}//url
		
		//->$2
		PA_Variable *pParam2 = ((PA_Variable *)pParams[1]);
		pParam2->fFiller = 0;
		pParam2->uValue.fArray.fCurrent = param2.uValue.fArray.fCurrent;
		pParam2->uValue.fArray.fNbElements = param2.uValue.fArray.fNbElements;
		pParam2->uValue.fArray.fData = param2.uValue.fArray.fData;

		//->$3
		PA_Variable *pParam3 = ((PA_Variable *)pParams[2]);
		pParam3->fFiller = 0;
		pParam3->uValue.fArray.fCurrent = param3.uValue.fArray.fCurrent;
		pParam3->uValue.fArray.fNbElements = param3.uValue.fArray.fNbElements;
		pParam3->uValue.fArray.fData = param3.uValue.fArray.fData;
		
		//->$4
		CFDictionarySetValue(returnOptions, CFSTR("rawImageDisplayBundleID"), QLPreviewTypeGetRawImageDisplayBundleID());
		CFDictionarySetValue(returnOptions, CFSTR("rawImageContentType"), QLPreviewTypeGetRawImageContentType());
		CFIndex displayBundleCount = QLPreviewTypeGetDisplayBundleCount();
		CFTypeRef intValue = CFNumberCreate (NULL, kCFNumberIntType, &displayBundleCount);
		CFDictionarySetValue(returnOptions, CFSTR("displayBundleCount"), intValue);
		CFRelease(intValue);
		
		setOptions((PA_Unistring *)pParams[3], returnOptions);
		CFRelease(returnOptions);
	}
}

