import { Modal, Form, Input, Select, InputRef, Tag, Tooltip, Radio, message } from 'antd';
import { PlusOutlined, FunnelPlotOutlined } from '@ant-design/icons';
import { useState, useRef, useEffect } from 'react';
import ReactQuill from 'react-quill';
import 'react-quill/dist/quill.snow.css';

function JobModal(props: any) {
  const [form] = Form.useForm();
  const [description, setDescription] = useState('Description');
  const [requirements, setRequirements] = useState('Requirements');
  const [stages, setStages] = useState<string[]>([]);
  const [stageInputVisible, setStageInputVisible] = useState(false);
  const [stageInputValue, setStageInputValue] = useState('');
  const [stageEditInputIndex, setStageEditInputIndex] = useState(-1);
  const [stageEditInputValue, setStageEditInputValue] = useState('');
  const [alwaysNull, _] = useState(null);
  const [location, setLocation] = useState('onsite');
  const stageInputRef = useRef<InputRef>(null);
  const stageEditInputRef = useRef<InputRef>(null);

  useEffect(() => {
    if (stageInputVisible) {
      stageInputRef.current?.focus();
    }
  }, [stageInputVisible]);

  useEffect(() => {
    stageEditInputRef.current?.focus();
  }, [stageInputValue]);

  const handleClose = (removedStage: string) => {
    const newStages = stages.filter(stage => stage !== removedStage);
    setStages(newStages);
  };

  const showInput = () => {
    setStageInputVisible(true);
  };

  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setStageInputValue(e.target.value);
  };

  const handleInputConfirm = () => {
    if (stageInputValue && stages.indexOf(stageInputValue) === -1) {
      setStages([...stages, stageInputValue]);
    }
    setStageInputVisible(false);
    setStageInputValue('');
  };

  const handleEditInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setStageEditInputValue(e.target.value);
  };

  const handleEditInputConfirm = () => {
    const newStages = [...stages];
    newStages[stageEditInputIndex] = stageEditInputValue;
    setStages(newStages);
    setStageEditInputIndex(-1);
    setStageInputValue('');
  };

  const onPipelineCopyChanged = (value) => {
    setStages(JSON.parse(props.jobs.find((j) => j.id === value).pipeline));
  };

  const onFinish = async (values) => {
    const body = { ...values, pipeline: stages, requirements, description };
    const response = await fetch(process.env.REACT_APP_API_URL + '/jobs/', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(body),
    });
    if (response.status === 201) {
      message.success('Job created successfully');
      props.refetch();
    } else
      message.error('Failed to create the job');
  };

  const onFinishFailed = () => {

  };

  return (
    <Modal
      title={props?.values ? "Edit job" : "New job"}
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
        initialValues={props?.values}
        name="basic"
        form={form}
        onFinish={onFinish}
        onFinishFailed={onFinishFailed}
        autoComplete="off"
      >
        <div style={{ display: 'grid', gridTemplateColumns: '50% 49%', gap: '10px' }}>
          <div>
            <Form.Item
              name="title"
              rules={[{ required: true, message: 'Please enter the title' }]}
              style={{ display: 'inline-block', width: '100%' }}
            >
              <Input placeholder="Title" />
            </Form.Item>
          </div>

          <div>
            <Form.Item
              name="department"
              rules={[{ required: false }]}
              style={{ display: 'inline-block', width: '100%' }}
            >
              <Select
                placeholder="Department"
                allowClear
              >
                {props?.departments?.map((d) => (
                  <Select.Option value={d?.id}>{d?.name}</Select.Option>
                ))}
              </Select>
            </Form.Item>
          </div>

          <div style={{ marginBottom: '20px' }}>
            <FunnelPlotOutlined style={{ marginRight: '5px' }} />
            <span style={{ fontWeight: 'bold' }}>Pipeline: </span>
            {stages.map((stage, index) => {
              if (stageEditInputIndex === index) {
                return (
                  <Input
                    ref={stageEditInputRef}
                    key={stage}
                    size="small"
                    className="tag-input"
                    value={stageEditInputValue}
                    onChange={handleEditInputChange}
                    onBlur={handleEditInputConfirm}
                    onPressEnter={handleEditInputConfirm}
                  />
                );
              }

              const isLongTag = stage.length > 20;

              const tagElem = (
                <Tag
                  className="edit-tag"
                  key={stage}
                  closable={true}
                  onClose={() => handleClose(stage)}
                >
                  <span
                    onDoubleClick={e => {
                      if (index !== 0) {
                        setStageEditInputIndex(index);
                        setStageEditInputValue(stage);
                        e.preventDefault();
                      }
                    }}
                  >
                    {isLongTag ? `${stage.slice(0, 20)}...` : stage}
                  </span>
                </Tag>
              );
              return isLongTag ? (
                <Tooltip title={stage} key={stage}>
                  {tagElem}
                </Tooltip>
              ) : (
              tagElem
              );
            })}
            {stageInputVisible && (
              <Input
                ref={stageInputRef}
                type="text"
                size="small"
                className="tag-input"
                value={stageInputValue}
                onChange={handleInputChange}
                onBlur={handleInputConfirm}
                onPressEnter={handleInputConfirm}
              />
            )}
            {!stageInputVisible && (
              <Tag className="site-tag-plus" onClick={showInput}>
                <PlusOutlined /> New Stage
              </Tag>
            )}

          </div>

          <Select
            placeholder="Copy pipeline from existing job"
            value={alwaysNull}
            onChange={onPipelineCopyChanged}
          >
            {props?.jobs?.map((j) => (
              <Select.Option value={j.id}>{j.title}</Select.Option>
            ))}
          </Select>


          <ReactQuill theme="snow" value={description} onChange={setDescription} />
          <ReactQuill theme="snow" value={requirements} onChange={setRequirements} />

        </div>

        <hr style={{ marginTop: '75px', marginBottom: '25px' }}/>
        <div style={{ display: 'grid', gridTemplateColumns: '50% 49%', gap: '10px' }}>
          <Select placeholder="Recruiter" allowClear>
            {props?.users?.map((u) => (
              <Select.Option value={u.id}>{u.username}</Select.Option>
            ))}
          </Select>
          <Select placeholder="Hiring manager" allowClear>
            {props?.users?.map((u) => (
              <Select.Option value={u.id}>{u.username}</Select.Option>
            ))}
          </Select>


        </div>

        <hr style={{ marginTop: '25px', marginBottom: '25px' }}/>
        <div style={{ display: 'grid', gridTemplateColumns: '33% 66%', gap: '10px' }}>
          <Radio.Group value={location} onChange={(e) => setLocation(e.target.value)}>
            <Radio value={'onsite'}>On-site</Radio>
            <Radio value={'hybrid'}>Hybrid</Radio>
            <Radio value={'remote'}>Remote</Radio>
          </Radio.Group>

          <Input placeholder="Address"></Input>
        </div>


        <hr style={{ marginTop: '25px', marginBottom: '25px' }}/>
        <div style={{ display: 'grid', gridTemplateColumns: '33% 33% 33%', gap: '10px' }}>
        </div>
      </Form>
    </Modal>
  )
}

export default JobModal;
