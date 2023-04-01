import { Modal, Form, Input, Select, Avatar, Button, Upload, message } from 'antd';
import { PhoneOutlined, MailOutlined, UserOutlined, ShoppingOutlined, CloseOutlined, EnvironmentOutlined } from '@ant-design/icons';
import styled from 'styled-components';
import { useEffect, useState } from 'react';
import { UploadOutlined } from '@ant-design/icons';
import type { RcFile, UploadFile, UploadProps } from 'antd/es/upload/interface';
import { PlusOutlined } from '@ant-design/icons';
import type { InputRef } from 'antd';
import { Tag, Tooltip } from 'antd';
import React, { useRef } from 'react';

const AvatarStyled = styled.div`
*:hover {
  background-color: green;
}
pointer: cursor;
margin-bottom: 8px;
`;

function NewCandidateModal(props: any) {
  const [form] = Form.useForm();
  const [steps, setSteps] = useState([]);
  const [chosenJob, setChosenJob] = useState('');
  const [uploading, setUploading] = useState(false);
  const [resumeFilename, setResumeFilename] = useState(null);
  const [avatarFilename, setAvatarFilename] = useState(null);
  const [tags, setTags] = useState<string[]>([]);
  const [inputVisible, setInputVisible] = useState(false);
  const [inputValue, setInputValue] = useState('');
  const [editInputIndex, setEditInputIndex] = useState(-1);
  const [editInputValue, setEditInputValue] = useState('');
  const inputRef = useRef<InputRef>(null);
  const editInputRef = useRef<InputRef>(null);
  const [skills, setSkills] = useState<string[]>([]);
  const [skillsInputVisible, setSkillsInputVisible] = useState(false);
  const [skillsInputValue, setSkillsInputValue] = useState('');
  const [editSkillsInputIndex, setSkillsEditInputIndex] = useState(-1);
  const [editSkillsInputValue, setSkillsEditInputValue] = useState('');
  const skillsInputRef = useRef<InputRef>(null);
  const editSkillsInputRef = useRef<InputRef>(null);
  const [languages, setLanguages] = useState<string[]>([]);
  const [languagesInputVisible, setLanguagesInputVisible] = useState(false);
  const [languagesInputValue, setLanguagesInputValue] = useState('');
  const [editLanguagesInputIndex, setLanguagesEditInputIndex] = useState(-1);
  const [editLanguagesInputValue, setLanguagesEditInputValue] = useState('');
  const languagesInputRef = useRef<InputRef>(null);
  const editLanguagesInputRef = useRef<InputRef>(null);



  useEffect(() => {
    if (inputVisible) {
      inputRef.current?.focus();
    }
  }, [inputVisible]);

  useEffect(() => {
    editInputRef.current?.focus();
  }, [inputValue]);

  const handleClose = (removedTag: string) => {
    const newTags = tags.filter(tag => tag !== removedTag);
    setTags(newTags);
  };

  const showInput = () => {
    setInputVisible(true);
  };

  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setInputValue(e.target.value);
  };

  const handleInputConfirm = () => {
    if (inputValue && tags.indexOf(inputValue) === -1) {
      setTags([...tags, inputValue]);
    }
    setInputVisible(false);
    setInputValue('');
  };

  const handleEditInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setEditInputValue(e.target.value);
  };

  const handleEditInputConfirm = () => {
    const newTags = [...tags];
    newTags[editInputIndex] = editInputValue;
    setTags(newTags);
    setEditInputIndex(-1);
    setInputValue('');
  };

  useEffect(() => {
    if (skillsInputVisible) {
      skillsInputRef.current?.focus();
    }
  }, [skillsInputVisible]);

  useEffect(() => {
    editSkillsInputRef.current?.focus();
  }, [skillsInputValue]);

  const handleSkillsClose = (removedTag: string) => {
    const newSkills = skills.filter(tag => tag !== removedTag);
    setSkills(newSkills);
  };

  const showSkillsInput = () => {
    setSkillsInputVisible(true);
  };

  const handleSkillsInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setSkillsInputValue(e.target.value);
  };

  const handleSkillsInputConfirm = () => {
    if (skillsInputValue && skills.indexOf(skillsInputValue) === -1) {
      setSkills([...skills, skillsInputValue]);
    }
    setSkillsInputVisible(false);
    setSkillsInputValue('');
  };

  const handleSkillsEditInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setSkillsEditInputValue(e.target.value);
  };

  const handleSkillsEditInputConfirm = () => {
    const newSkills = [...skills];
    newSkills[editSkillsInputIndex] = editSkillsInputValue;
    setSkills(newSkills);
    setSkillsEditInputIndex(-1);
    setSkillsInputValue('');
  };


  useEffect(() => {
    if (languagesInputVisible) {
      languagesInputRef.current?.focus();
    }
  }, [languagesInputVisible]);

  useEffect(() => {
    editLanguagesInputRef.current?.focus();
  }, [languagesInputValue]);

  const handleLanguagesClose = (removedTag: string) => {
    const newLanguages = languages.filter(tag => tag !== removedTag);
    setLanguages(newLanguages);
  };

  const showLanguagesInput = () => {
    setLanguagesInputVisible(true);
  };

  const handleLanguagesInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setLanguagesInputValue(e.target.value);
  };

  const handleLanguagesInputConfirm = () => {
    if (languagesInputValue && languages.indexOf(languagesInputValue) === -1) {
      setLanguages([...languages, languagesInputValue]);
    }
    setLanguagesInputVisible(false);
    setLanguagesInputValue('');
  };

  const handleLanguagesEditInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setLanguagesEditInputValue(e.target.value);
  };

  const handleLanguagesEditInputConfirm = () => {
    const newLanguages = [...languages];
    newLanguages[editLanguagesInputIndex] = editLanguagesInputValue;
    setLanguages(newLanguages);
    setLanguagesEditInputIndex(-1);
    setLanguagesInputValue('');
  };



  useEffect(() => {
    if (chosenJob?.length)
      setSteps(JSON.parse(props.jobs.filter((j) => j.id === chosenJob)[0].pipeline));
  }, [chosenJob]);

  const handleUpload = (file) => {
    const formData = new FormData();
    formData.append('file', file as RcFile);
    if (['pdf', 'doc', 'docx'].includes(file.name.split('.').pop().toLowerCase()) === false) {
      message.error('Only PDF, DOC, and DOCX files are allowed');
      return;
    }
    setUploading(true);
    fetch(process.env.REACT_APP_API_URL + '/resume/' + file.name, {
      method: 'PUT',
      body: formData,
    })
    .then(res => res.json())
    .then((r) => {
      setResumeFilename(r.filename);
      message.success('Uploaded successfully');
    })
    .catch((e) => {
      message.error('Upload failed');
    })
    .finally(() => {
      setUploading(false);
    });
  };

  const handleAvatarUpload = (file) => {
    const formData = new FormData();
    formData.append('file', file as RcFile);
    if (['jpg', 'jpeg', 'png'].includes(file.name.split('.').pop().toLowerCase()) === false) {
      message.error('Only JPEG and PNG files are allowed');
      return;
    }
    fetch(process.env.REACT_APP_API_URL + '/avatar/' + file.name, {
      method: 'PUT',
      body: formData,
    })
    .then(res => res.json())
    .then((r) => {
      setAvatarFilename(r.filename);
      message.success('Uploaded successfully');
    })
    .catch((e) => {
      message.error('Upload failed');
    })
  };


  const uploadProps: UploadProps = {
    onRemove: file => {
    },
    beforeUpload: file => {
      handleUpload(file);
      return false;
    },
    fileList: [],
  };

  const avatarUploadProps: UploadProps = {
    onRemove: file => {
    },
    beforeUpload: file => {
      handleAvatarUpload(file);
      return false;
    },
    fileList: [],
  };


  const onFinish = async (values) => {
    let response = await fetch(process.env.REACT_APP_API_URL + '/candidates/', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({...values, resume_filename: resumeFilename}),
    });
    if (response.status === 201) {
      props.refetch();
      message.success('Candidate created successfully');
    } else
      message.error('Failed to create the candidate');
  };

  const onFinishFailed = () => {

  };

  const onJobChange = (value: string) => {
    setChosenJob(value);
  };

  return (
    <Modal
      title="New candidate"
      centered
      open={props.open}
      onOk={() => {
        form.submit();
        props.setOpen(false)
      }}
      onCancel={() => {
        form.resetFields();
        props.setOpen(false)
      }}
      width={1000}
    >
      <Form
        name="basic"
        form={form}
        initialValues={{ remember: true }}
        onFinish={onFinish}
        onFinishFailed={onFinishFailed}
        autoComplete="off"
      >
        <div style={{ display: 'grid', gridTemplateColumns: '20% 40% 40%', gap: '10px' }}>
          <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', gridRow: '1/3' }}>
            <Upload {...avatarUploadProps}>
            <AvatarStyled>
              {avatarFilename ?
                <Avatar size={64} src={process.env.REACT_APP_STATIC_URL + '/' + avatarFilename} style={{ cursor: 'pointer' }} />
              :
              <Avatar size={64} icon={<UserOutlined />} style={{ cursor: 'pointer' }} />}
            </AvatarStyled>
            </Upload>
            <Upload {...uploadProps}><Button loading={uploading} type='primary' icon={<UploadOutlined />}>Upload CV</Button></Upload>
            {resumeFilename && (<>
              <span style={{ color: 'darkgreen' }}>CV is attached <CloseOutlined onClick={() => setResumeFilename(null)}/></span>
            </>)}
          </div>

          <div>
            <UserOutlined style={{marginTop: '8px', marginRight: '4px' }} />
            <Form.Item
              name="fullname"
              rules={[{ required: true, message: 'Please enter the full name' }]}
              style={{ display: 'inline-block', width: '90%' }}
            >
              <Input placeholder="Full name" />
            </Form.Item>
          </div>

          <div>
            <MailOutlined style={{ marginTop: '8px', marginRight: '4px' }}/>
            <Form.Item
              name="email"
              rules={[{ required: false }]}
              style={{ display: 'inline-block', width: '90%' }}
            >
              <Input placeholder="Email" />
            </Form.Item>
          </div>

          <div>
            <PhoneOutlined style={{ marginTop: '8px', marginRight: '4px' }}/>
            <Form.Item
              name="phone"
              rules={[{ required: false }]}
              style={{ display: 'inline-block', width: '90%' }}
            >
              <Input placeholder="Phone number" />
            </Form.Item>
          </div>



          <div>
            <ShoppingOutlined style={{ marginTop: '8px', marginRight: '4px' }} />
            <Form.Item
              name="job"
              rules={[{ required: false }]}
              style={{ display: 'inline-block', width: '45%' }}
            >
              <Select
                placeholder="Job"
                onChange={onJobChange}
                allowClear
              >
                {props?.jobs?.map((j) => (
                  <Select.Option value={j.id}>{j.title}</Select.Option>
                ))}
              </Select>
            </Form.Item>
            <Form.Item
              name="stage"
              rules={[{ required: false }]}
              style={{ display: 'inline-block', width: '45%' }}
            >
              <Select
                placeholder="Stage"
                disabled={!!!chosenJob?.length}
                allowClear
              >
                {steps?.map((s, i) => (
                  <Select.Option value={i}>{s}</Select.Option>
                ))}
              </Select>
            </Form.Item>


          </div>


        </div>

          

        <div style={{ marginTop: '10px' }}>
          <div style={{ display: 'grid', gridTemplateColumns: '50% 25% 25%', gap: '10px' }}>
            <div>
              <EnvironmentOutlined style={{ marginTop: '8px', marginRight: '4px' }}/>
              <Form.Item
                name="address"
                rules={[{ required: false }]}
                style={{ display: 'inline-block', width: '95%' }}
              >
                <Input placeholder="Address" />
              </Form.Item>
            </div>
            <div>
            <EnvironmentOutlined style={{ marginTop: '8px', marginRight: '4px' }}/>
            <Form.Item
              name="timezone"
              rules={[{ required: false }]}
              style={{ display: 'inline-block', width: '90%' }}
            >
              <Input placeholder="Timezone" />
            </Form.Item>
            </div>
            <div>
              <EnvironmentOutlined style={{ marginTop: '8px', marginRight: '4px' }}/>
              <Form.Item
                name="salaryExpectation"
                rules={[{ required: false }]}
                style={{ display: 'inline-block', width: '90%' }}
              >
                <Input placeholder="Salary expectation" />
              </Form.Item>

          </div>
        </div>
        </div>

        <div style={{ display: 'grid', gridTemplateColumns: '33% 33% 33%', gap: '10px' }}>
          <div>
            <div style={{ width: '100%' }}>            {inputVisible && (
              <Input
                ref={inputRef}
                type="text"
                size="small"
                style={{ width: '100%' }}
                className="tag-input"
                value={inputValue}
                onChange={handleInputChange}
                onBlur={handleInputConfirm}
                onPressEnter={handleInputConfirm}
              />
            )}
              {!inputVisible && (
                <Tag className="site-tag-plus" onClick={showInput} style={{ width: '100%' }}>
                  <PlusOutlined /> New Tag
                </Tag>
              )}
            </div>

            {tags.map((tag, index) => {
              if (editInputIndex === index) {
                return (
                  <Input
                    ref={editInputRef}
                    key={tag}
                    size="small"
                    className="tag-input"
                    value={editInputValue}
                    onChange={handleEditInputChange}
                    onBlur={handleEditInputConfirm}
                    onPressEnter={handleEditInputConfirm}
                  />
                );
              }

              const isLongTag = tag.length > 20;

              const tagElem = (
                <Tag
                  className="edit-tag"
                  key={tag}
                  closable={true}
                  onClose={() => handleClose(tag)}
                >
                  <span
                    onDoubleClick={e => {
                      if (index !== 0) {
                        setEditInputIndex(index);
                        setEditInputValue(tag);
                        e.preventDefault();
                      }
                    }}
                  >
                    {isLongTag ? `${tag.slice(0, 20)}...` : tag}
                  </span>
                </Tag>
              );
              return isLongTag ? (
                <Tooltip title={tag} key={tag}>
                  {tagElem}
                </Tooltip>
              ) : (
              tagElem
              );
            })}
          </div>

          <div>
            <div style={{ width: '100%' }}>            {skillsInputVisible && (
              <Input
                ref={skillsInputRef}
                type="text"
                size="small"
                style={{ width: '100%' }}
                className="tag-input"
                value={skillsInputValue}
                onChange={handleSkillsInputChange}
                onBlur={handleSkillsInputConfirm}
                onPressEnter={handleSkillsInputConfirm}
              />
            )}
              {!skillsInputVisible && (
                <Tag className="site-tag-plus" onClick={showSkillsInput} style={{ width: '100%' }}>
                  <PlusOutlined /> New Skill
                </Tag>
              )}
            </div>

            {skills.map((tag, index) => {
              if (editSkillsInputIndex === index) {
                return (
                  <Input
                    ref={editSkillsInputRef}
                    key={tag}
                    size="small"
                    className="tag-input"
                    value={editSkillsInputValue}
                    onChange={handleSkillsEditInputChange}
                    onBlur={handleSkillsEditInputConfirm}
                    onPressEnter={handleSkillsEditInputConfirm}
                  />
                );
              }

              const isLongTag = tag.length > 20;

              const tagElem = (
                <Tag
                  className="edit-tag"
                  key={tag}
                  closable={true}
                  onClose={() => handleSkillsClose(tag)}
                >
                  <span
                    onDoubleClick={e => {
                      if (index !== 0) {
                        setSkillsEditInputIndex(index);
                        setSkillsEditInputValue(tag);
                        e.preventDefault();
                      }
                    }}
                  >
                    {isLongTag ? `${tag.slice(0, 20)}...` : tag}
                  </span>
                </Tag>
              );
              return isLongTag ? (
                <Tooltip title={tag} key={tag}>
                  {tagElem}
                </Tooltip>
              ) : (
              tagElem
              );
            })}
          </div>

          <div>
            <div style={{ width: '100%' }}>            {languagesInputVisible && (
              <Input
                ref={languagesInputRef}
                type="text"
                size="small"
                style={{ width: '100%' }}
                className="tag-input"
                value={languagesInputValue}
                onChange={handleLanguagesInputChange}
                onBlur={handleLanguagesInputConfirm}
                onPressEnter={handleLanguagesInputConfirm}
              />
            )}
              {!languagesInputVisible && (
                <Tag className="site-tag-plus" onClick={showLanguagesInput} style={{ width: '100%' }}>
                  <PlusOutlined /> New Language
                </Tag>
              )}
            </div>

            {languages.map((tag, index) => {
              if (editLanguagesInputIndex === index) {
                return (
                  <Input
                    ref={editLanguagesInputRef}
                    key={tag}
                    size="small"
                    className="tag-input"
                    value={editLanguagesInputValue}
                    onChange={handleLanguagesEditInputChange}
                    onBlur={handleLanguagesEditInputConfirm}
                    onPressEnter={handleLanguagesEditInputConfirm}
                  />
                );
              }

              const isLongTag = tag.length > 20;

              const tagElem = (
                <Tag
                  className="edit-tag"
                  key={tag}
                  closable={true}
                  onClose={() => handleLanguagesClose(tag)}
                >
                  <span
                    onDoubleClick={e => {
                      if (index !== 0) {
                        setLanguagesEditInputIndex(index);
                        setLanguagesEditInputValue(tag);
                        e.preventDefault();
                      }
                    }}
                  >
                    {isLongTag ? `${tag.slice(0, 20)}...` : tag}
                  </span>
                </Tag>
              );
              return isLongTag ? (
                <Tooltip title={tag} key={tag}>
                  {tagElem}
                </Tooltip>
              ) : (
              tagElem
              );
            })}
          </div>



          </div>





      </Form>
    </Modal>
  )
}

export default NewCandidateModal;
