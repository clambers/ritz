{
  "targets": [
    {
      "target_name": "ritz",
      "cflags": [ "-std=c++14", "-fexceptions" ],
      "conditions": [
        ["OS!='win'", {
          "cflags+": [ "-std=c++14", "-fexceptions" ],
          "cflags_c+": [ "-std=c++14", "-fexceptions" ],
          "cflags_cc+": [ "-std=c++14", "-fexceptions" ]
        }],
        ["OS=='mac'", {
          "xcode_settings": {
            "OTHER_CPLUSPLUSFLAGS": [ "-std=c++14", "-fexceptions" ],
            "MACOSX_DEPLOYMENT_TARGET": "10.7"
          }
        }]
      ],
      "sources": [ "src/ritz.cc" ]
    }
  ]
}
