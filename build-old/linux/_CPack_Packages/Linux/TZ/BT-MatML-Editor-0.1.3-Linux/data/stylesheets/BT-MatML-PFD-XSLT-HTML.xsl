<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
  <xsl:output method="html" indent="yes" name="html" />
  <xsl:key name="MaterialId" match="Material" use="@id" />
  <xsl:variable name="btheader">
    <div style="page-break-before:always">
      <a>
        <img src="Images/hr-line.png" style="display:block; border-width:0px" />
      </a>
    </div>
    <div>
      <a href="http://www.bellshiretechnologies.com">
        <img src="Images/Bellshire Technologies Inc.png" style="display:block; border-width:0px" />
      </a>
    </div>
    <div>
      <a>
        <img src="Images/hr-line.png" style="display:block; border-width:0px" />
      </a>
    </div>
  </xsl:variable>
  <xsl:template match="MatML_Doc">
    <xsl:result-document href="./Database_Materials-PFD.html" method="html" encoding="ISO-8859-1">
      <html>
        <head>
          <title>Bellshire Technologies Inc. - Process Flow Diagram</title>
          <style>
          body, td, th { font-family:Verdana, Arial, helvetica, sans-serif; font-size:x-small; }
        </style>
        </head>
        <body STYLE=" background-color:#ffffff">
          <div>
            <xsl:copy-of select="$btheader" />
            <H1>Process Flow Diagram</H1>
            <xsl:for-each select="Material[position()=last()]">
              <div>
                <table valign="top" width="85%">
                  <tbody>
                    <tr>
                      <td>
                        <div align="center">
                          <h3>FINAL COMPONENT<br /><a href="{concat(@id,&quot;-Costing.html&quot;)}" name="{@id}"><span><xsl:value-of select="./BulkDetails/Name" /></span></a></h3>
                        </div>
                        <div align="center">
                          <ul>
                            <xsl:for-each select="./BulkDetails/ProcessingDetails[Name!=&quot;Costing&quot;]">
                              <li>
                                <xsl:value-of select="Name" />
                              </li>
                            </xsl:for-each>
                          </ul>
                        </div>
                        <xsl:call-template name="nextlevel"></xsl:call-template>
                      </td>
                    </tr>
                  </tbody>
                </table>
              </div>
            </xsl:for-each>
          </div>
        </body>
      </html>
    </xsl:result-document>
  </xsl:template>
  <xsl:template name="nextlevel">
    <xsl:if test="count(./ComponentDetails)&gt;1">
      <div>
        <img src="Images/gather1.png" width="100%" align="center"></img>
      </div>
    </xsl:if>
    <div>
      <table border="0" valign="top">
        <tbody>
          <tr>
            <xsl:for-each select="ComponentDetails">
              <xsl:if test="count(./preceding-sibling::ComponentDetails)&lt;1 or not(preceding-sibling::ComponentDetails[./Class]/Class[./ParentMaterial]/ParentMaterial/@id=./Class[./ParentMaterial]/ParentMaterial/@id)">
                <!--count(./preceding-sibling::ComponentDetails)<1 or not(preceding-sibling::ComponentDetails[./Class]/Class[./ParentMaterial]/ParentMaterial/@id=./Class[./ParentMaterial]/ParentMaterial/@id)-->
                <xsl:variable name="curid" select="./Class[./ParentMaterial]/ParentMaterial/@id"></xsl:variable>
                <xsl:variable name="tempnum" select="count(../ComponentDetails[./Class]/Class[./ParentMaterial]/ParentMaterial[./@id=$curid]/@id)"></xsl:variable>
                <xsl:choose>
                  <xsl:when test="./Class[./Name][Name=&quot;RAW&quot;]">
                    <td valign="top" align="center">
                      <table>
                        <tbody>
                          <tr>
                            <td>
                              <div>
                                <img src="Images/uparrow1.png" align="right"></img>
                              </div>
                            </td>
                            <td>
                              <div>
                                <ul>
                                  <xsl:for-each select="./ProcessingDetails[Name!=&quot;Costing&quot;]">
                                    <li>
                                      <xsl:value-of select="Name" />
                                    </li>
                                  </xsl:for-each>
                                </ul>
                              </div>
                            </td>
                          </tr>
                        </tbody>
                      </table>
                      <div>
                        <h3>
                          <xsl:value-of select="Name"></xsl:value-of>
                          <br />(RAW MATERIAL)</h3>
                      </div>
                    </td>
                  </xsl:when>
                  <xsl:when test="key('MaterialId',./Class[./ParentMaterial]/ParentMaterial/@id)">
                    <td>
                      <div align="center">
                        <table>
                          <tbody>
                            <tr>
                              <td>
                                <img src="Images/uparrow1.png" style="display:block; border-width:0px;vertical-align:top;text-align:center"></img>
                              </td>
                              <td>
                                <ul>
                                  <xsl:for-each select="./ProcessingDetails[Name!='Costing']">
                                    <li>
                                      <xsl:value-of select="Name" />
                                    </li>
                                  </xsl:for-each>
                                </ul>
                              </td>
                            </tr>
                          </tbody>
                        </table>
                        <br />
                        <div>
                          <h3>
                            <!-- <a href="{concat(@id,&quot;-Costing.html&quot;)}" name="{@id}"> -->
                            <a href="{concat(./Class[./ParentMaterial]/ParentMaterial/@id,&quot;-Costing.html&quot;)}" name="{./Class[./ParentMaterial]/ParentMaterial/@id}">
                              <span>
                                <xsl:value-of select="concat($tempnum,&quot;X &quot;,key('MaterialId',./Class[./ParentMaterial]/ParentMaterial/@id)/BulkDetails/Name)" />
                              </span>
                            </a>
                          </h3>
                        </div>
                      </div>
                      <div align="center">
                        <ul>
                          <xsl:for-each select="key('MaterialId',./Class[./ParentMaterial]/ParentMaterial/@id)/BulkDetails/ProcessingDetails[Name!=&quot;Costing&quot;]">
                            <li>
                              <xsl:value-of select="Name" />
                            </li>
                          </xsl:for-each>
                        </ul>
                      </div>
                      <xsl:for-each select="key('MaterialId',./Class[./ParentMaterial]/ParentMaterial/@id)">
                        <xsl:call-template name="nextlevel"></xsl:call-template>
                      </xsl:for-each>
                    </td>
                  </xsl:when>
                  <xsl:otherwise>
                    <td align="center" valign="top">
                      <div>
                        <table>
                          <tbody>
                            <tr>
                              <td>
                                <div>
                                  <img src="Images/uparrow1.png" align="right"/>
                                </div>
                              </td>
                              <td>
                                <div>
                                  <ul>
                                    <xsl:for-each select="./ProcessingDetails[Name!=&quot;Costing&quot;]">
                                      <li>
                                        <xsl:value-of select="Name" />
                                      </li>
                                    </xsl:for-each>
                                  </ul>
                                </div>
                              </td>
                            </tr>
                          </tbody>
                        </table>
                        <div>
                          <h3>
                            <xsl:value-of select="concat(&quot;1X &quot;,Name)"></xsl:value-of>
                          </h3>
                        </div>
                      </div>
                    </td>
                  </xsl:otherwise>
                </xsl:choose>
              </xsl:if>
            </xsl:for-each>
          </tr>
        </tbody>
      </table>
    </div>
  </xsl:template>
</xsl:stylesheet>